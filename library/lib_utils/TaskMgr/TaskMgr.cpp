#include "TaskMgr.h"


using namespace std::literals;

namespace egt
{
namespace TaskMgr
{


struct TaskContext
{
    TaskContext();
    ~TaskContext();

    void _register();
    void _unregister();
    //
    struct Invocation
    {
        Function callback;
        bool hasSentinel = false;
        std::weak_ptr<void> sentinel;
    };

    std::atomic_bool m_shouldStop = {false};
    std::mutex m_invokesLocker;
    std::vector<Invocation> m_invokes;
    std::vector<Invocation> m_processingInvokes;
    size_t m_invokesBegin = 0;
    //
    bool m_hasEmptyEvent = false;
    std::condition_variable m_wakeupEvent;
    //
    Id m_id;
    std::thread::id m_threadId;
    friend struct TaskMgr;
    bool m_registered = false;
};

static std::thread::id s_mainThreadId = std::this_thread::get_id();
static std::unordered_map<TaskMgr::Id, TaskMgr::TaskContext*> s_tasks[EGT_TASK_MGR_CONTENTION];
static std::unordered_map<std::thread::id, TaskMgr::Id> s_threadIds[EGT_TASK_MGR_CONTENTION];
static std::atomic_uint_fast64_t s_freeTaskId = {1};
static std::mutex s_mainLocker[EGT_TASK_MGR_CONTENTION];
static std::atomic_uint s_contentionIdx = {0};

namespace priv
{

thread_local static ::egt::TaskMgr::TaskContext ___threadLockal_thisTask_;

void _invoke(TaskMgr::Id taskId, bool hasSentinel, std::weak_ptr<void> sentinel,
                      Function&& callback)
{
    if(callback == nullptr)
    {
        return;
    }
    unsigned int idx = s_contentionIdx.fetch_add(1) % EGT_TASK_MGR_CONTENTION;
    s_mainLocker[idx].lock();
    auto it = s_tasks[idx].find(taskId);
    if(it == s_tasks[idx].end())
    {
        s_mainLocker[idx].unlock();
        return;
    }
    auto& remoteTask = *(it->second);
    s_mainLocker[idx].unlock();
    
    remoteTask.m_invokesLocker.lock();
    remoteTask.m_invokes.emplace_back(TaskContext::Invocation());
    remoteTask.m_invokes.back().callback = std::move(callback);
    if(true == hasSentinel)
    {
        remoteTask.m_invokes.back().sentinel = sentinel;
        remoteTask.m_invokes.back().hasSentinel = true;
    }
    //
    remoteTask.m_wakeupEvent.notify_all();
    remoteTask.m_invokesLocker.unlock();
}

}




TaskContext::TaskContext() = default;
//
TaskContext::~TaskContext()
{
    _unregister();
}

void TaskContext::_register()
{
    if(m_registered)
    {
        return;
    }
    m_id = TaskMgr::s_freeTaskId.fetch_add(1);
    for (unsigned int i = 0; i < EGT_TASK_MGR_CONTENTION; i++)
    {
        std::lock(TaskMgr::s_mainLocker[i], m_invokesLocker);
        std::lock_guard<std::mutex> lk1(TaskMgr::s_mainLocker[i], std::adopt_lock);
        std::lock_guard<std::mutex> lk2(m_invokesLocker, std::adopt_lock);
        
        //
        m_threadId = std::this_thread::get_id();

        TaskMgr::s_tasks[i][m_id] = this;
        TaskMgr::s_threadIds[i][m_threadId] = m_id;
    }
    m_registered = true;
}

void TaskContext::_unregister()
{
    for (unsigned int i = 0; i < EGT_TASK_MGR_CONTENTION; i++)
    {
        std::lock(TaskMgr::s_mainLocker[i], m_invokesLocker);
        std::lock_guard<std::mutex> lk1(TaskMgr::s_mainLocker[i], std::adopt_lock);
        std::lock_guard<std::mutex> lk2(m_invokesLocker, std::adopt_lock);
        
        //
        TaskMgr::s_tasks[i].erase(m_id);
        TaskMgr::s_threadIds[i].erase(m_threadId);
    }
    m_registered = false;
}

void Invoke(Id taskId, Function&& callback)
{
    priv::_invoke(taskId, false, {}, std::move(callback));
}

void Invoke(Id taskId, std::weak_ptr<void> sentinel, Function&& callback)
{
    priv::_invoke(taskId, true, sentinel, std::move(callback));
}

void RunOrInvoke(TaskMgr::Id taskId, Function&& callback)
{
    auto& thisTask = priv::___threadLockal_thisTask_;
    if(taskId == thisTask.m_id)
    {
        if(callback != nullptr)
        {
            callback();
        }
    }
    else
    {
        priv::_invoke(taskId, false, {}, std::move(callback));
    }
}

void RunOrInvoke(TaskMgr::Id taskId, std::weak_ptr<void> sentinel, Function&& callback)
{
    auto& thisTask = priv::___threadLockal_thisTask_;
    if(taskId == thisTask.m_id)
    {
        if(callback != nullptr)
        {
            auto locker = sentinel.lock();
            if(nullptr != locker)
            {
                callback();
            }
        }
    }
    else
    {
        priv::_invoke(taskId, true, sentinel, std::move(callback));
    }
}

void PostEmptyEvent(Id taskId)
{
    unsigned int idx = s_contentionIdx.fetch_add(1) % EGT_TASK_MGR_CONTENTION;
    s_mainLocker[idx].lock();
    auto it = s_tasks[idx].find(taskId);
    if(it == s_tasks[idx].end())
    {
        s_mainLocker[idx].unlock();
        return;
    }
    auto& remoteTask = *(it->second);
    s_mainLocker[idx].unlock();
    
    remoteTask.m_invokesLocker.lock();
    remoteTask.m_hasEmptyEvent = true;
    remoteTask.m_wakeupEvent.notify_all();
    remoteTask.m_invokesLocker.unlock();
}

void Stop(Id taskId)
{
    unsigned int idx = s_contentionIdx.fetch_add(1) % EGT_TASK_MGR_CONTENTION;
    s_mainLocker[idx].lock();
    auto it = s_tasks[idx].find(taskId);
    if(it == s_tasks[idx].end())
    {
        s_mainLocker[idx].unlock();
        return;
    }
    auto& remoteTask = *(it->second);
    s_mainLocker[idx].unlock();
    
    remoteTask.m_invokesLocker.lock();
    remoteTask.m_hasEmptyEvent = true;
    remoteTask.m_shouldStop.store(true);
    remoteTask.m_wakeupEvent.notify_all();
    remoteTask.m_invokesLocker.unlock();
}

void Invoke(std::thread::id threadId, Function&& callback)
{
    const auto p = GetId(threadId);
    if (p.first == false)
    {
        return;
    }
    auto taskId = p.second;
    
    priv::_invoke(taskId, false, {}, std::move(callback));
}

void Invoke(std::thread::id threadId, std::weak_ptr<void> sentinel, Function&& callback)
{
    const auto p = GetId(threadId);
    if (p.first == false)
    {
        return;
    }
    auto taskId = p.second;
    priv::_invoke(taskId, true, sentinel, std::move(callback));
}

void RunOrInvoke(std::thread::id threadId, Function&& callback)
{
    const auto p = GetId(threadId);
    if (p.first == false)
    {
        return;
    }
    auto taskId = p.second;
    RunOrInvoke(taskId, std::move(callback));
}

void RunOrInvoke(std::thread::id threadId, std::weak_ptr<void> sentinel, Function&& callback)
{
    const auto p = GetId(threadId);
    if (p.first == false)
    {
        return;
    }
    auto taskId = p.second;
    RunOrInvoke(taskId, sentinel, std::move(callback));
}

void PostEmptyEvent(std::thread::id threadId)
{
    const auto p = GetId(threadId);
    if (p.first == false)
    {
        return;
    }
    auto taskId = p.second;
    PostEmptyEvent(taskId);
}

void Stop(std::thread::id threadId)
{
    const auto p = GetId(threadId);
    if (p.first == false)
    {
        return;
    }
    auto taskId = p.second;
    Stop(taskId);
}

Task::Ptr RunTask()
{
    Task::Ptr task = std::make_shared<Task>();
    std::mutex lockMutex;
    std::unique_lock<std::mutex> locker(lockMutex);
    std::condition_variable cv;
    task->taskThread = std::thread([&lockMutex, &cv]() {
        RegisterThisThread();
        lockMutex.lock();
        cv.notify_all();
        lockMutex.unlock();
        //
        while(TaskMgr::ShouldStop() == false)
        {
            TaskMgr::WaitEvent();
        }
    });
    cv.wait(locker);
    //
    auto threadId = task->taskThread.get_id();
    const auto p = TaskMgr::GetId(threadId);
    
    if(p.first == false)
    {
        return nullptr;
    }
    task->taskId = p.second;
    return task;
}

void RegisterThisThread()
{
    auto& thisTask = priv::___threadLockal_thisTask_;
    thisTask._register();
}

std::thread::id MainThreadId()
{
    return s_mainThreadId;
}

Id GetId() noexcept
{
    auto& thisTask = priv::___threadLockal_thisTask_;
    return thisTask.m_id;
}

std::pair<bool, TaskMgr::Id> GetId(std::thread::id threadId)
{
    unsigned int idx = s_contentionIdx.fetch_add(1) % EGT_TASK_MGR_CONTENTION;
    std::lock_guard<std::mutex> locker(TaskMgr::s_mainLocker[idx]);
    auto it = TaskMgr::s_threadIds[idx].find(threadId);
    if(it == TaskMgr::s_threadIds[idx].end())
    {
        return {false, {}};
    }

    return {true, it->second};
}

std::pair<bool, std::thread::id> GetThreadId(TaskMgr::Id taskId)
{
    unsigned int idx = s_contentionIdx.fetch_add(1) % EGT_TASK_MGR_CONTENTION;
    std::lock_guard<std::mutex> locker(TaskMgr::s_mainLocker[idx]);
    auto it = TaskMgr::s_tasks[idx].find(taskId);
    if(it == TaskMgr::s_tasks[idx].end())
    {
        return {false, {}};
    }
    return {true, it->second->m_threadId};
}

bool ShouldStop()
{
    auto& thisTask = priv::___threadLockal_thisTask_;
    auto shouldStop = thisTask.m_shouldStop.load();
    return shouldStop;
}

bool _processQueue(std::unique_lock<std::mutex>& locker)
{
    auto& thisTask = priv::___threadLockal_thisTask_;
    if (thisTask.m_invokes.empty() && thisTask.m_processingInvokes.size() == thisTask.m_invokesBegin)
    {
        return false;
    }
    
    while(false == thisTask.m_invokes.empty() || thisTask.m_processingInvokes.size() != thisTask.m_invokesBegin)
    {
        if (thisTask.m_processingInvokes.size() == thisTask.m_invokesBegin)
        {
            thisTask.m_processingInvokes.clear();
            std::swap(thisTask.m_processingInvokes, thisTask.m_invokes);
            thisTask.m_invokesBegin = 0;
        }
        
        locker.unlock();
        while(thisTask.m_invokesBegin < thisTask.m_processingInvokes.size())
        {
            auto invocation = std::move(thisTask.m_processingInvokes[thisTask.m_invokesBegin++]);
            
            //
            if(true == invocation.hasSentinel)
            {
                auto sentinelLock = invocation.sentinel.lock();
                if(nullptr != sentinelLock)
                {
                    invocation.callback();
                }
            }
            else
            {
                invocation.callback();
            }
        }
        locker.lock();
        //
        
    }
    thisTask.m_processingInvokes.clear();
    thisTask.m_invokesBegin = 0;
    return true;
}

void Sleep(Duration duration)
{
    auto endTime = Clock::now() + duration;
    auto& thisTask = priv::___threadLockal_thisTask_;

    std::unique_lock<std::mutex> thisTaskLocker(thisTask.m_invokesLocker);
    _processQueue(thisTaskLocker);
    while(Clock::now() < endTime)
    {
        if(TaskMgr::ShouldStop() == true)
        {
            return;
        }
        auto timeLeft = endTime - Clock::now();
        if(timeLeft > Duration(0))
        {
            thisTask.m_wakeupEvent.wait_for(thisTaskLocker, timeLeft);
        }

        _processQueue(thisTaskLocker);
    }
}

void WaitEvent(Duration duration)
{
    auto& thisTask = priv::___threadLockal_thisTask_;

    std::unique_lock<std::mutex> thisTaskLocker(thisTask.m_invokesLocker);
    if(true == _processQueue(thisTaskLocker))
    {
        return;
    }
    if(TaskMgr::ShouldStop() == true)
    {
        return;
    }
    if (thisTask.m_hasEmptyEvent == true)
    {
        thisTask.m_hasEmptyEvent = false;        
        return;
    }
    thisTask.m_wakeupEvent.wait_for(thisTaskLocker, duration);
    _processQueue(thisTaskLocker);
}

void WaitEvent()
{
    auto& thisTask = priv::___threadLockal_thisTask_;

    std::unique_lock<std::mutex> thisTaskLocker(thisTask.m_invokesLocker);
    if(true == _processQueue(thisTaskLocker))
    {
        return;
    }
    if(TaskMgr::ShouldStop() == true)
    {
        return;
    }
    if (thisTask.m_hasEmptyEvent == true)
    {
        thisTask.m_hasEmptyEvent = false;
        return;
    }
    thisTask.m_wakeupEvent.wait(thisTaskLocker);
    _processQueue(thisTaskLocker);
}

Task::~Task()
{
    TaskMgr::Stop(taskId);
    if(taskThread.joinable())
    {
        taskThread.join();
    }
}

void Invoke(Task::Ptr task, Function &&callback)
{
    Invoke(task->taskId, std::move(callback));
}

void Invoke(Task::Ptr task, std::weak_ptr<void> sentinel, Function &&callback)
{
    Invoke(task->taskId, sentinel, std::move(callback)); 
}

void Invoke(const std::thread &thread, Function &&callback)
{
    Invoke(thread.get_id(), std::move(callback)); 
}

void Invoke(const std::thread &thread, std::weak_ptr<void> sentinel, Function &&callback)
{
    Invoke(thread.get_id(), sentinel, std::move(callback)); 
}

void RunOrInvoke(Task::Ptr task, Function &&callback)
{
    RunOrInvoke(task->taskId, std::move(callback));
}

void RunOrInvoke(Task::Ptr task, std::weak_ptr<void> sentinel, Function &&callback)
{
    RunOrInvoke(task->taskId, sentinel, std::move(callback));
}

void RunOrInvoke(const std::thread &thread, Function &&callback)
{
    RunOrInvoke(thread.get_id(), std::move(callback));    
}

void RunOrInvoke(const std::thread &thread, std::weak_ptr<void> sentinel, Function &&callback)
{
    RunOrInvoke(thread.get_id(), sentinel, std::move(callback));    
}

void PostEmptyEvent(Task::Ptr task)
{
    PostEmptyEvent(task->taskId);
}

void PostEmptyEvent(const std::thread &thread)
{
    PostEmptyEvent(thread.get_id());
}

void Stop(Task::Ptr task)
{
    Stop(task->taskId);
}

void Stop(const std::thread &thread)
{
    Stop(thread.get_id());
}

bool IsValidTaskId(Id taskId) noexcept
{
    return (taskId != InvalidTaskId) && (taskId != EmptyTaskId);
}

}
}
