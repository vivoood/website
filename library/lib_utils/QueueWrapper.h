#ifndef __QUEUE_WRAPPER__
#define __QUEUE_WRAPPER__

#include <mutex>
#include <deque>
#include <memory>
#include <semaphore.h>
#include <atomic>

template <class T> class CQueueWrapper
{
public:
    CQueueWrapper()
        : m_bRunning(true)
    {
        InitQueueSemaphore();
    }

    ~CQueueWrapper() {}
    CQueueWrapper(const CQueueWrapper<T> &) {}
    CQueueWrapper<T>& operator =(const CQueueWrapper<T> &) {}

    void PushBack( T item )
    {
        std::lock_guard<std::mutex> lockGuard(m_Mutex);
        m_Deque.push_back(item);
        SignalQueue();
    }

    T GetFront()
    {
        std::lock_guard<std::mutex> lockGuard(m_Mutex);
        if ( m_Deque.empty() ) {
            return NULL;
        }
        return m_Deque.front();
    }

    void PopFront()
    {
        std::lock_guard<std::mutex> lockGuard(m_Mutex);
        if ( m_Deque.empty() ) {
            return;
        }
        m_Deque.pop_front();
    }

    unsigned int Count()
    {
        std::lock_guard<std::mutex> lockGuard(m_Mutex);
        return m_Deque.size();
    }

    void Clear()
    {
        std::lock_guard<std::mutex> lockGuard(m_Mutex);
        m_Deque.clear();
    }

    bool Empty()
    {
        std::lock_guard<std::mutex> lockGuard(m_Mutex);
        return m_Deque.empty();
    }

    void Quit()
    {
        m_bRunning = false;
        SignalQueue();
    }

    void StartRunning()
    {
        m_bRunning = true;
    }

    bool Running()
    {
        return m_bRunning;
    }

    void Wait()
    {
        sem_wait(&semaphore);
    }

protected:
    void SignalQueue()
    {
        sem_post(&semaphore);
    }

    void InitQueueSemaphore()
    {
        sem_init(&semaphore, 0, 0);
    }

protected:
    std::mutex      m_Mutex;
    std::deque<T>   m_Deque;

    sem_t semaphore;
    std::atomic<bool> m_bRunning;
};
#endif /* __QUEUE_WRAPPER__ */
