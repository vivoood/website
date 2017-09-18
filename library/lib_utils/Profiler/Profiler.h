#ifndef __EGT_OLD_PROFILER_H__
#define __EGT_OLD_PROFILER_H__

//#define EGT_CPU_PROFILING_ON

#define OLD_PROFILER_ON
#if defined(OLD_PROFILER_ON)

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
// temp
#include "ModuleMonitor.h"

using namespace std::literals;

#if defined(EGT_CPU_PROFILING_ON)
#define EGT_BLOCK_PROFILING(...)    \
    egt::Profiler::BlockProfilingObject ____tmpBlockProfilingObj_(egt::Profiler::GetInstance(), __VA_ARGS__);
#else
#define EGT_BLOCK_PROFILING(...)
#endif //EGT_CPU_PROFILING_ON

namespace egt {

#define PROFILER_START_TAG ('@')

class Profiler
{
public:
    class BlockProfilingObject
    {
    public:
        template< typename... Args > BlockProfilingObject(Profiler* profiler, Args... args)
            : m_profiler(profiler)
            , m_profilerStarted( (profiler == nullptr) ? false : profiler->m_profilerStarted.load() )
            , systemStartTime(0)
            , cpuStartTime(0)
            , startMemoryUsage(0)
        {
            if (m_profilerStarted)
            {
                m_profiler->AddStartTag(args...);
            }
        }
        ~BlockProfilingObject();
    private:
        BlockProfilingObject();
        BlockProfilingObject( const BlockProfilingObject& );
        BlockProfilingObject( BlockProfilingObject& );
        BlockProfilingObject( volatile const BlockProfilingObject& );
        BlockProfilingObject( volatile BlockProfilingObject& );
        BlockProfilingObject& operator=(BlockProfilingObject);
        BlockProfilingObject& operator=(BlockProfilingObject&& );
        BlockProfilingObject& operator=(const BlockProfilingObject& );

        Profiler* m_profiler;
        bool m_profilerStarted;
        uint64_t systemStartTime;
        uint64_t cpuStartTime;
        uint64_t startMemoryUsage;
    };

    struct Tag
    {
        std::string name;
        int64_t systemTime;
        timespec cpuTime;
        bool hasMemInfo;
        int64_t memUsage; // bytes
        std::vector<Tag> children;
    };

    virtual ~Profiler();

    void StartProfiling();
    bool IsStarted() const;
    void StopProfiling();
    void SetCpuProfilingDepth(unsigned int depth);
    void SetMemProfilingDepth(unsigned int depth);
    unsigned int GetCpuProfilingDepth() const;
    unsigned int GetMemProfilingDepth() const;

    std::map<std::thread::id, std::vector<Tag>> DumpTags();
    std::vector<uint8_t> DumpAndDestroyRawBuff();

    static Profiler* GetInstance();
    static void Init();
    static void Init(Profiler* profiler);
    static void Deinit();

private:
    Profiler();
    void AddStartTag(const char* tagName);
    template< typename... Args > void AddStartTag(Args... args)
    {
        auto& context = m_profilerContexts.GetContext();
        if (context.depth > m_maxFuncProfilingDepth) {context.depth++;return;}
        auto& buffer = context.buffer;
        ProfilerInlines::Write8(buffer, PROFILER_START_TAG);
        size_t buf_size = buffer.size();
        buffer.resize(buf_size + 4096);
        int len = snprintf((char *)&buffer[buf_size], 4096, args...);
        if (len < 4096)
            buffer.resize(buf_size + len + 1);

        AddStartTagInfo();
    }
    void AddStartTagInfo();
    void AddEndTag();

    size_t ReadTag(std::vector<uint8_t>& buff, size_t idx, Tag& tag);
    size_t ReadStartTag(std::vector<uint8_t>& buff, size_t idx, Tag& tag);
    size_t ReadEndTag(std::vector<uint8_t>& buff, size_t idx, Tag& startTag);

    struct ThreadContext
    {
        std::string             name;
        std::thread::id         threadId;
        std::vector<uint8_t>    buffer;
        unsigned int depth;
    };


    struct ProfilerContext
    {
        std::map<std::thread::id, ThreadContext> m_threadContexts;
        std::mutex m_contextLocker;
        std::condition_variable cv;
        int read_cnt;
        int write_cnt;
        void GetReadLock();
        void GetWriteLock();
        void ReleaseWriteLock();
        void ReleaseReadLock();
        ProfilerContext() : read_cnt(0), write_cnt(0) {}
        ThreadContext& GetContext();
    };
    ProfilerContext m_profilerContexts;
    std::atomic_bool m_profilerStarted;
    unsigned int m_maxMemProfilingDepth = 2;
    unsigned int m_maxFuncProfilingDepth = 16;


    static Profiler* s_profilerInstance;
    friend class BlockProfilingObject;
};

}

#else
#include "ProfilerNew.h"
#endif

#endif // __EGT_OLD_PROFILER_H__
