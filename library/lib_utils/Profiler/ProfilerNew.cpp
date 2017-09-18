
#include "ProfilerNew.h"

#if defined(NEW_PROFILER_ON)

#include <chrono>
#include <lib_utils/UniStream/UniStream.h>
#include <time.h>

namespace profiler_local
{
struct ProfilerThreadContextLifeMgr
{
    ProfilerThreadContextLifeMgr() = default;
    ~ProfilerThreadContextLifeMgr()
    {
        ::egt::Profiler::CleanupThread();
    }
};

thread_local static ::egt::Profiler::ThreadContext* s_threadContext = nullptr;
thread_local static ProfilerThreadContextLifeMgr s_contextLifeMgr;
}
namespace egt
{
Profiler* Profiler::s_profilerInstance = nullptr;

/////////////////////////////////////////////////////////////////////////////
// Profiler::ThreadContext
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
Profiler::ThreadContext* Profiler::ThreadContext::GetInstance()
{
    return ::profiler_local::s_threadContext;
}

/////////////////////////////////////////////////////////////////////////////
template <>
oUniStream& operator<<(oUniStream& out, const Profiler::ThreadContext::TagHeader& tag)
{
    // out << currency.ToCents();
    return out << tag.cpuTime << tag.sysTime << tag.buff;
}

/////////////////////////////////////////////////////////////////////////////
template <>
iUniStream& operator>>(iUniStream& in, Profiler::ThreadContext::TagHeader& tag)
{
    return in >> tag.cpuTime >> tag.sysTime >> tag.buff;
}

/////////////////////////////////////////////////////////////////////////////
Profiler::ThreadContext::Snapshot* Profiler::ThreadContext::GetNextSnapshot()
{
    std::lock_guard<std::mutex> locker(timelineLocker);
    auto dataStart = timeline.data();
    auto res = dataStart + (timelineStartIdx + timelineSize) % timeline.size();
    if(timelineSize < timeline.size())
    {
        ++timelineSize;
    }
    else
    {
        ++timelineStartIdx;
    }
    (*res).clear();
    return res;
}

/////////////////////////////////////////////////////////////////////////////
void Profiler::ThreadContext::DumpData(oUniStream& serializer)
{
    std::lock_guard<std::mutex> locker(timelineLocker);
    serializer << name;
    if(timelineSize < 2)
    {
        serializer << 0ul;
        return;
    }

    serializer << (timelineSize - 1);
    for(size_t i = timelineStartIdx; i < timelineStartIdx + timelineSize - 1; i++)
    {
        serializer << timeline[i % timeline.size()];
    }
}

/////////////////////////////////////////////////////////////////////////////
// Profiler
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
Profiler* Profiler::GetInstance()
{
    return s_profilerInstance;
}

///////////////////////////////////////////////////////////////////////////
void Profiler::Init()
{
    if(nullptr == s_profilerInstance)
    {
        s_profilerInstance = new Profiler();
    }
}

///////////////////////////////////////////////////////////////////////////
void Profiler::Init(Profiler* profiler)
{
    if(nullptr == s_profilerInstance)
    {
        s_profilerInstance = profiler;
    }
}

///////////////////////////////////////////////////////////////////////////
void Profiler::Deinit()
{
    if(nullptr == s_profilerInstance)
    {
        delete s_profilerInstance;
        s_profilerInstance = nullptr;
    }
}

///////////////////////////////////////////////////////////////////////////
void Profiler::StartProfiling()
{
    std::lock_guard<std::mutex> locker(m_threadsLocker);
    for(auto& p : m_threadContexts)
    {
        auto& ctx = p.second;
        if(true == ctx->isProfilingStarted.load())
        {
            continue;
        }
        ctx->timelineStartIdx = 0;
        ctx->timelineSize = 0;
        ctx->isProfilingStarted.store(true);
    }
    m_profilerStarted.store(true);
}

///////////////////////////////////////////////////////////////////////////
bool Profiler::IsStarted() const
{
    return m_profilerStarted.load();
}

///////////////////////////////////////////////////////////////////////////
void Profiler::Serialize(std::vector<uint8_t>& outBuff)
{
    oUniStream serializer;
    std::lock_guard<std::mutex> locker(m_threadsLocker);
    serializer << m_threadContexts.size();
    for(auto& p : m_threadContexts)
    {
        auto& ctx = p.second;
        ctx->DumpData(serializer);
    }
    outBuff = std::move(serializer.GetBuffer());
}

///////////////////////////////////////////////////////////////////////////
void Profiler::StopProfiling()
{
    std::lock_guard<std::mutex> locker(m_threadsLocker);
    for(auto& p : m_threadContexts)
    {
        auto& ctx = p.second;
        ctx->isProfilingStarted.store(false);
    }
    m_profilerStarted.store(false);
}

///////////////////////////////////////////////////////////////////////////
void Profiler::SetCpuProfilingDepth(unsigned int depth)
{
    std::lock_guard<std::mutex> locker(m_threadsLocker);
    for(auto& p : m_threadContexts)
    {
        auto& ctx = p.second;
        std::lock_guard<std::mutex> ctxLocker(ctx->timelineLocker);
        ctx->maxDepth = depth;
    }
}

///////////////////////////////////////////////////////////////////////////
void Profiler::RegisterThread(const std::string& name)
{
    auto profiler = Profiler::GetInstance();
    if(profiler == nullptr)
    {
        return;
    }
    auto id = std::this_thread::get_id();

    { // LOCK
        std::lock_guard<std::mutex> locker(profiler->m_threadsLocker);
        profiler->m_threadContexts[id] = std::make_unique<Profiler::ThreadContext>();
        ::profiler_local::s_threadContext = profiler->m_threadContexts[id].get();
    }
    auto context = ::profiler_local::s_threadContext;
    //
    context->name = name;
    context->timeline.resize(1200);
    context->timelineStartIdx = 0;
    context->timelineSize = 0;
}

///////////////////////////////////////////////////////////////////////////
void Profiler::CleanupThread()
{
    auto profiler = Profiler::GetInstance();
    if(profiler == nullptr)
    {
        return;
    }

    // LOCK
    std::lock_guard<std::mutex> locker(profiler->m_threadsLocker);
    auto it = profiler->m_threadContexts.find(std::this_thread::get_id());
    if(it == profiler->m_threadContexts.end())
    {
        return;
    }
    profiler->m_threadContexts.erase(it);
}
}
#endif
