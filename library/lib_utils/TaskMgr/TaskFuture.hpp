#ifndef EGT_TASK_FUTURE_HPP
#define EGT_TASK_FUTURE_HPP

#include "TaskMgr.h"

namespace egt
{
namespace TaskMgr
{


template<typename R>
struct Result
{
    enum class Status : unsigned
    {
        NotReady,
        Ready,
        Error
    };
    
    
    R value = {};
    
    std::atomic<Id> futureTaskId = {EmptyTaskId};
    std::atomic<Status> status = {Status::NotReady};
};

template<typename T>
class Promise;

template<typename T>
class Future;

template<typename T>
std::pair<Future<T>, Promise<T>> MakeFuturePromisePair();

template <typename T>
class Future
{
    using ResultType = Result<T>;
    std::shared_ptr<ResultType> result;
    friend std::pair<Future<T>, Promise<T>> MakeFuturePromisePair<T>();
public:
    Future() = default;
    Future(const Future& rhs) = default;
    Future& operator=(const Future& rhs) = default;
    
    Future(Future&& rhs)
        : result(std::move(rhs.result))
    {
    }
        
    Future& operator=(Future&& rhs)
    {
        result = std::move(rhs.result);
    }
    
    bool Wait()
    {
        auto myTaskId = result->futureTaskId.exchange(TaskMgr::GetId());
        if (myTaskId == TaskMgr::EmptyTaskId)
        {
            while(result->status.load() == ResultType::Status::NotReady)
            {
                TaskMgr::WaitEvent();
            }
        }
        
        return result->status.load() == ResultType::Status::Ready;
    }
    
    T CopyGet()
    {
        Wait();
        return result->value;
    }
    T MoveGet()
    {
        Wait();
        return std::move(result->value);
    }
    
    bool IsReady() const
    {
        return result->status.load() == ResultType::Status::Ready;
    }
    
    bool HasError() const
    {
        return result->status.load() == ResultType::Status::Error;
    }
};

template <typename T>
class Promise
{

    using ResultType = Result<T>;
    std::shared_ptr<ResultType> result;
    
    friend std::pair<Future<T>, Promise<T>> MakeFuturePromisePair<T>();
    
public:
    Promise() = default;
    Promise(const Promise& rhs) = default;
    Promise& operator=(const Promise& rhs) = default;
    
    Promise(Promise&& rhs)
        : result(std::move(rhs.result))
    {
    }
        
    Promise& operator=(Promise&& rhs)
    {
        result = std::move(rhs.result);
    }
    
    
    ~Promise()
    {
        if (result && result->status == ResultType::Status::NotReady)
        {
            _setStatus(ResultType::Status::Error);
        }
    }

    void Set(T&& value)
    {
        //result->locker.lock();
        result->value = std::move(value);
        _setStatus(ResultType::Status::Ready);
    }

private:
    void _setStatus(typename ResultType::Status status)
    {
        result->status = status;
        auto futureTaskId = result->futureTaskId.exchange(TaskMgr::InvalidTaskId);
        //
        if (TaskMgr::IsValidTaskId(futureTaskId))
        {
            TaskMgr::PostEmptyEvent(futureTaskId);
        }
    }
};

template<typename T>
std::pair<Future<T>, Promise<T>> MakeFuturePromisePair()
{
    auto sharedState = std::make_shared<Result<T>>();
    std::pair<Future<T>, Promise<T>> pair;
    pair.first.result = sharedState;
    pair.second.result = sharedState;
    
    return pair;
}

}
}

#endif // EGT_TASK_FUTURE_HPP
