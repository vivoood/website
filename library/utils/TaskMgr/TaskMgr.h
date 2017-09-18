#ifndef EGT_TASK_MGR_H
#define EGT_TASK_MGR_H
//
#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>
#include <chrono>
//

#define EGT_TASK_MGR_CONTENTION (1)
namespace egt
{

namespace TaskMgr
{
    using Id = uint64_t;
    constexpr Id EmptyTaskId = 0ull;
    constexpr Id InvalidTaskId = ~(0ull);
    using Function = std::function<void()>;
    //
    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::high_resolution_clock::duration;
    
    //
    struct Task : public std::enable_shared_from_this<Task>
    {
        using Ptr = std::shared_ptr<Task>;
        Id taskId;
        std::thread taskThread;
        ~Task();
        Task() = default;
        Task(const Task&) = delete;
        Task(Task&&) = default;
        Task& operator=(Task&&) = default;
        Task& operator=(const Task&) = delete;
    };
    //
    void RegisterThisThread();
    // Ids
    std::thread::id MainThreadId();
    Id GetId() noexcept;
    std::pair<bool, Id> GetId(std::thread::id threadId);
    std::pair<bool, std::thread::id> GetThreadId(Id taskId);
    // My task
    bool ShouldStop();
    //
    bool IsValidTaskId(Id taskId) noexcept;
    //
    void Sleep(Duration duration);
    void WaitEvent(Duration duration);
    void WaitEvent();
    // Remote task
    void Invoke(Task::Ptr task, Function&& callback);
    void Invoke(Task::Ptr task, std::weak_ptr<void> sentinel, Function&& callback);
    void Invoke(const std::thread& thread, Function&& callback);
    void Invoke(const std::thread& thread, std::weak_ptr<void> sentinel, Function&& callback);
    void Invoke(Id taskId, Function&& callback);
    void Invoke(Id taskId, std::weak_ptr<void> sentinel, Function&& callback);
    void Invoke(std::thread::id threadId, Function&& callback);
    void Invoke(std::thread::id threadId, std::weak_ptr<void> sentinel, Function&& callback);
    //
    void RunOrInvoke(Task::Ptr task, Function&& callback);
    void RunOrInvoke(Task::Ptr task, std::weak_ptr<void> sentinel, Function&& callback);
    void RunOrInvoke(const std::thread& thread, Function&& callback);
    void RunOrInvoke(const std::thread& thread, std::weak_ptr<void> sentinel, Function&& callback);
    void RunOrInvoke(Id taskId, Function&& callback);
    void RunOrInvoke(Id taskId, std::weak_ptr<void> sentinel, Function&& callback);
    void RunOrInvoke(std::thread::id threadId, Function&& callback);
    void RunOrInvoke(std::thread::id threadId, std::weak_ptr<void> sentinel, Function&& callback);
    //
    void PostEmptyEvent(Task::Ptr task);  
    void PostEmptyEvent(const std::thread& thread);
    void PostEmptyEvent(Id taskId);  
    void PostEmptyEvent(std::thread::id threadId);
    //
    void Stop(Task::Ptr task);
    void Stop(const std::thread& thread);
    void Stop(Id taskId);
    void Stop(std::thread::id threadId);
    //
    // New tasks
    Task::Ptr RunTask();
}
}
#endif // EGT_TASK_MGR_H
