#ifndef EGT_PROFILER_H
#define EGT_PROFILER_H

//#define NEW_PROFILER_ON
#if defined(NEW_PROFILER_ON)

#include <vector>
#include <string>
#include <cstdint>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <map>
#include "ProfilerInlines.h"
#include <cstdarg>
#include <memory>

#include "ProfilerInlines.h"


// temp
#include "ModuleMonitor.h"

#if defined(EGT_CPU_PROFILING_ON)
#define EGT_BLOCK_PROFILING(...)    \
    ::egt::Profiler::BlockProfilingObject ____tmpBlockProfilingObj_(__VA_ARGS__);
#else
#defing EGT_BLOCK_PROFILING(...)
#endif //EGT_CPU_PROFILING_ON

#define PROFILER_START_TAG ('~')
#define PROFILER_END_TAG ('@')
namespace egt {

class oUniStream;

class Profiler
{
public:

    virtual ~Profiler() = default;

    void StartProfiling();
    void StopProfiling();
    void SetCpuProfilingDepth(unsigned int depth);
    bool IsStarted() const;
    void Serialize(std::vector<uint8_t>& outBuff);

    static Profiler* GetInstance();
    static void Init();
    static void Init(Profiler* profiler);
    static void Deinit();
    static void RegisterThread(const std::string& name);
    static void CleanupThread();
    //


private:
    Profiler() = default;

public:
    struct ThreadContext
    {
        struct TagHeader
        {
            // in nano seconds
            int64_t cpuTime;
            int64_t sysTime;
            char buff[32];
        };

        using Snapshot = std::vector<TagHeader>;
        std::vector<Snapshot> timeline;
        //
        std::string name;
        Snapshot* currentSnapshot = nullptr;
        std::thread::id threadId = std::this_thread::get_id();
        size_t timelineStartIdx = 0;
        size_t timelineSize = 0;
        std::mutex timelineLocker;
        unsigned int currentDepth = 0;
        unsigned int maxDepth = 16;
        std::atomic_bool isProfilingStarted = {false};

        // return
        // and false: otherwise
        inline const char* AddStartTag(const char* tagName);

        inline void AddEndTag(const char* tagName);
        //
        Snapshot* GetNextSnapshot();
        void DumpData(oUniStream& serializer);
        static ThreadContext* GetInstance();
    };

    std::mutex m_threadsLocker;
    std::unordered_map<std::thread::id, std::unique_ptr<ThreadContext>> m_threadContexts;

    std::atomic_bool m_profilerStarted = {false};

    static Profiler* s_profilerInstance;
public:
    class BlockProfilingObject
    {
    public:
        BlockProfilingObject(const char* format);
        //
        template<typename T1, typename ... Args>
        BlockProfilingObject(const char* format, const T1& t1, Args&&...args);

        //
        ~BlockProfilingObject();

    private:
        BlockProfilingObject() = delete;
        BlockProfilingObject( const BlockProfilingObject& ) = delete;
        BlockProfilingObject( BlockProfilingObject& ) = delete;
        BlockProfilingObject( volatile const BlockProfilingObject& ) = delete;
        BlockProfilingObject( volatile BlockProfilingObject& ) = delete;
        BlockProfilingObject& operator=(BlockProfilingObject) = delete;
        BlockProfilingObject& operator=(BlockProfilingObject&& ) = delete;
        BlockProfilingObject& operator=(const BlockProfilingObject& ) = delete;

    private:
        char tagName[64];
        Profiler::ThreadContext* threadContext;
        const char* tagNamePart2;
    };


    friend struct ThreadContext;
    friend class BlockProfilingObject;
};


inline const char* Profiler::ThreadContext::AddStartTag(const char* tagName)
{
    if (0 == currentDepth)
    {
        // init
        currentSnapshot = GetNextSnapshot();
    }

    currentDepth++;
    //
    auto& buff = *currentSnapshot;
    buff.resize(buff.size()+1);
    auto& header = buff.back();

    header.cpuTime = ProfilerInlines::GetThreadCpuTime();
    header.sysTime = ProfilerInlines::GetMonotonicNano();
    
    //
    header.buff[0] = PROFILER_START_TAG;
    char* dst = &(header.buff[1]);
    char* dstMax = &(header.buff[0]) + sizeof(header.buff);

    while((dst < dstMax) && (*dst++ = *tagName++));

    return tagName - 1;
}

inline void Profiler::ThreadContext::AddEndTag(const char* tagName)
{
    currentDepth--;
    //
    auto& buff = *currentSnapshot;
    buff.resize(buff.size()+1);
    auto& header = buff.back();


    header.cpuTime = ProfilerInlines::GetThreadCpuTime();
    header.sysTime = ProfilerInlines::GetMonotonicNano();
    //
    header.buff[0] = PROFILER_END_TAG;
    char* dst = &(header.buff[1]);
    char* dstMax = &(header.buff[0]) + sizeof(header.buff);

    if (*tagName++ == 0)
    {
        return;
    }
    while((dst < dstMax) && (*dst++ = *tagName++));
}


inline Profiler::BlockProfilingObject::BlockProfilingObject(const char* format)
{
    threadContext = ThreadContext::GetInstance();
    if (threadContext == nullptr)
    {
        return;
    }

    if (threadContext->isProfilingStarted.load() == false)
    {
        threadContext = nullptr;
        return;
    }

    if (threadContext->currentDepth >= threadContext->maxDepth)
    {
        threadContext = nullptr;
        return;
    }
    //
    strncpy(tagName, format, sizeof(tagName)-1);
    tagName[sizeof(tagName)-1] = 0;
    tagNamePart2 = threadContext->AddStartTag(tagName);
}

template<typename T1, typename ... Args>
inline Profiler::BlockProfilingObject::BlockProfilingObject(const char* format, const T1& t1, Args&&...args)
{
    threadContext = ThreadContext::GetInstance();
    if (threadContext == nullptr)
    {
        return;
    }

    if (threadContext->isProfilingStarted.load() == false)
    {
        threadContext = nullptr;
        return;
    }

    if (threadContext->currentDepth >= threadContext->maxDepth)
    {
        threadContext = nullptr;
        return;
    }
    //
    snprintf(tagName, sizeof(tagName), format, t1, std::forward<Args>(args)...);
    tagNamePart2 = threadContext->AddStartTag(tagName);
}


inline Profiler::BlockProfilingObject::~BlockProfilingObject()
{
    if (threadContext == nullptr)
    {
        return;
    }
    threadContext->AddEndTag(tagNamePart2);
}



}
#endif

#endif // EGT_PROFILER_H
