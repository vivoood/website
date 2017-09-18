#include "Profiler.h"


#include <lib_utils/GenericMsg/GenericMsg.h>
#include <lib_utils/UniStream/UniStream.h>
#include <lib_utils/Network/Messengers/Messenger.h>
#include <lib_utils/UniObject/UniMsg.h>

#include "Gl_Profiler.h"

#if defined(OLD_PROFILER_ON)

#include <time.h>
#include <chrono>

using namespace egt;
#define PROFILER_END_TAG ('#')
#define PROFILER_STRING_TERMINATOR ('\0')
#define PROFILER_MEM_INFO ('+')
#define PROFILER_MEM_INFO_SKIP ('-')

Profiler* Profiler::s_profilerInstance = nullptr;

///////////////////////////////////////////////////////////////////////////
Profiler* Profiler::GetInstance()
{
    return s_profilerInstance;
}

///////////////////////////////////////////////////////////////////////////
void Profiler::Init()
{
    if (nullptr == s_profilerInstance)
    {
        s_profilerInstance = new Profiler();
    }
}

///////////////////////////////////////////////////////////////////////////
void Profiler::Init(Profiler* profiler)
{
    if (nullptr == s_profilerInstance)
    {
        s_profilerInstance = profiler;
    }
}

///////////////////////////////////////////////////////////////////////////
void Profiler::Deinit()
{
    if (nullptr == s_profilerInstance)
    {
        delete s_profilerInstance;
        s_profilerInstance = nullptr;
    }
}

///////////////////////////////////////////////////////////////////////////
Profiler::ThreadContext &Profiler::ProfilerContext::GetContext()
{
    auto threadId = std::this_thread::get_id();
    GetReadLock();
    auto contextIter = m_threadContexts.find(threadId);
    ReleaseReadLock();

    if (m_threadContexts.end() == contextIter)
    {
        ThreadContext context;
        context.name = "";
        context.threadId = threadId;
        context.depth = 0;
        GetWriteLock();
        auto newContextIter = m_threadContexts.insert({threadId, context});
        ReleaseWriteLock();
        newContextIter.first->second.buffer.reserve(1024 * 1024 * 8);
        return newContextIter.first->second;
    }
    else
    {
        return contextIter->second;
    }
}

///////////////////////////////////////////////////////////////////////////
void Profiler::ProfilerContext::GetReadLock()
{
    std::unique_lock<std::mutex> lk(m_contextLocker);
    while (write_cnt)
    {
        cv.wait(lk);
        //lk.lock();
    }
    read_cnt++;
    lk.unlock();
}

///////////////////////////////////////////////////////////////////////////
void Profiler::ProfilerContext::GetWriteLock()
{
    std::unique_lock<std::mutex> lk(m_contextLocker);
    while (write_cnt || read_cnt)
    {
        cv.wait(lk);
        //lk.lock();
    }
    write_cnt++;
    lk.unlock();

}

///////////////////////////////////////////////////////////////////////////
void Profiler::ProfilerContext::ReleaseWriteLock()
{
    std::unique_lock<std::mutex> lk(m_contextLocker);
    write_cnt--;
    cv.notify_all();
    lk.unlock();
}

///////////////////////////////////////////////////////////////////////////
void Profiler::ProfilerContext::ReleaseReadLock()
{
    std::unique_lock<std::mutex> lk(m_contextLocker);
    read_cnt--;
    cv.notify_all();
    lk.unlock();
}

///////////////////////////////////////////////////////////////////////////
Profiler::Profiler()
    : m_profilerStarted(false)
{
}

///////////////////////////////////////////////////////////////////////////
Profiler::~Profiler()
{

}

void Profiler::AddStartTag(const char *tagName)
{

    auto& context = m_profilerContexts.GetContext();
    if (context.depth > m_maxFuncProfilingDepth) {context.depth++;return;}

    auto& buffer = context.buffer;
    ProfilerInlines::Write8(buffer, PROFILER_START_TAG);
    while(*tagName)
    {
        ProfilerInlines::Write8(buffer, *tagName);
        tagName++;
    }
    ProfilerInlines::Write8(buffer, PROFILER_STRING_TERMINATOR);
    AddStartTagInfo();
}

void Profiler::AddStartTagInfo()
{
    auto& context = m_profilerContexts.GetContext();
    auto& buffer = context.buffer;
    timespec cpuTime;
    ProfilerInlines::GetThreadCpuTime(cpuTime);
    int64_t systemTime = ProfilerInlines::GetMonotonicMicro();
    for(unsigned i = 0; i < sizeof(cpuTime); i++)
    {
        ProfilerInlines::Write8(buffer, ((uint8_t*)&cpuTime)[i]);
    }
    ProfilerInlines::Write64(buffer, systemTime);
    if (context.depth < m_maxMemProfilingDepth)
    {
        ProfilerInlines::Write8(buffer, PROFILER_MEM_INFO);
        uint64_t memUsage = ProfilerInlines::GetMemoryUsage();
        ProfilerInlines::Write64(buffer, memUsage);
    }
    else
    {
        ProfilerInlines::Write8(buffer, PROFILER_MEM_INFO_SKIP);
    }
    context.depth++;
}

///////////////////////////////////////////////////////////////////////////
void Profiler::AddEndTag()
{
    auto& context = m_profilerContexts.GetContext();
    if (context.depth > m_maxFuncProfilingDepth+1) {context.depth--;return;}

    auto& buffer = context.buffer;
    context.depth--;
    ProfilerInlines::Write8(buffer, PROFILER_END_TAG);
    timespec cpuTime;
    ProfilerInlines::GetThreadCpuTime(cpuTime);
    int64_t systemTime = ProfilerInlines::GetMonotonicMicro();
    for(unsigned i = 0; i < sizeof(cpuTime); i++)
    {
        ProfilerInlines::Write8(buffer, ((uint8_t*)&cpuTime)[i]);
    }
    ProfilerInlines::Write64(buffer, systemTime);

    if (context.depth < m_maxMemProfilingDepth)
    {
        ProfilerInlines::Write8(buffer, PROFILER_MEM_INFO);
        uint64_t memUsage = ProfilerInlines::GetMemoryUsage();
        ProfilerInlines::Write64(buffer, memUsage);
    }
    else
    {
        ProfilerInlines::Write8(buffer, PROFILER_MEM_INFO_SKIP);
    }
}

///////////////////////////////////////////////////////////////////////////
void Profiler::StartProfiling()
{
    if (m_profilerStarted)
    {
        return;
    }
    m_profilerContexts.m_threadContexts.clear();
    m_profilerContexts.read_cnt = 0;
    m_profilerContexts.write_cnt = 0;
    m_profilerStarted = true;
}

///////////////////////////////////////////////////////////////////////////
bool Profiler::IsStarted() const
{
    return m_profilerStarted;
}

///////////////////////////////////////////////////////////////////////////
void Profiler::StopProfiling()
{
    m_profilerStarted = false;
}

///////////////////////////////////////////////////////////////////////////
void Profiler::SetCpuProfilingDepth(unsigned int depth)
{
    m_maxFuncProfilingDepth = depth;
}

///////////////////////////////////////////////////////////////////////////
void Profiler::SetMemProfilingDepth(unsigned int depth)
{
    m_maxMemProfilingDepth = depth;
}

///////////////////////////////////////////////////////////////////////////
unsigned int Profiler::GetCpuProfilingDepth() const
{
    return m_maxFuncProfilingDepth;
}

///////////////////////////////////////////////////////////////////////////
unsigned int Profiler::GetMemProfilingDepth() const
{
    return m_maxMemProfilingDepth;
}

///////////////////////////////////////////////////////////////////////////
std::map<std::thread::id, std::vector<Profiler::Tag> > Profiler::DumpTags()
{
    std::map<std::thread::id, std::vector<Profiler::Tag> > result;
    for (auto& p : m_profilerContexts.m_threadContexts)
    {
        auto& context = p.second;
        size_t idx = 0;
        result[context.threadId] = {};

        auto& vec = result[context.threadId];

        while(idx < context.buffer.size())
        {
            Tag tag;
            idx++; // TODO: check if it is start tag
            idx = ReadTag(context.buffer, idx, tag);
            vec.push_back(std::move(tag));
        }
    }

    m_profilerContexts.m_threadContexts.clear();
    m_profilerContexts.read_cnt = 0;
    m_profilerContexts.write_cnt = 0;
    return result;
}

///////////////////////////////////////////////////////////////////////////
std::vector<uint8_t> Profiler::DumpAndDestroyRawBuff()
{
    std::vector<uint8_t> empty;
    if (m_profilerStarted)
    {
        return empty;
    }
    for (auto& p : m_profilerContexts.m_threadContexts)
    {
        auto& context = p.second;
        return std::move(context.buffer);
    }
    return empty;
}

///////////////////////////////////////////////////////////////////////////
size_t Profiler::ReadTag(std::vector<uint8_t> &buff, size_t idx, Profiler::Tag &tag)
{
    if (idx >= buff.size())
    {
        return idx;
    }
    // read bytes
    idx = ReadStartTag(buff, idx, tag);
    //
    uint8_t type;
    while(1)
    {
        idx = ProfilerInlines::Read8(buff, idx, type);
        if (type == PROFILER_START_TAG)
        {
            Tag childTag;
            tag.children.push_back(childTag);
            idx = ReadTag(buff, idx, tag.children.back());
        }
        else
        {
            break;
        }
    }

    // read end tag
    idx = ReadEndTag(buff, idx, tag);

    return idx;
}

///////////////////////////////////////////////////////////////////////////
size_t Profiler::ReadStartTag(std::vector<uint8_t> &buff, size_t idx, Profiler::Tag &tag)
{
    if (idx >= buff.size())
    {
        return idx;
    }

    tag.name = "";
    while(1)
    {
        uint8_t c;
        idx = ProfilerInlines::Read8(buff, idx, c);
        if (PROFILER_STRING_TERMINATOR == c)
        {
            break;
        }
        tag.name.push_back(c);
    }

    timespec cpuTime;
    uint64_t systemTime;

    for(unsigned i = 0; i < sizeof(cpuTime); i++)
    {
        idx = ProfilerInlines::Read8(buff, idx, ((uint8_t*)&cpuTime)[i]);
    }

    idx = ProfilerInlines::Read64(buff, idx, systemTime);

    uint8_t hasMemInfo;
    idx = ProfilerInlines::Read8(buff, idx, hasMemInfo);
    tag.hasMemInfo = hasMemInfo == PROFILER_MEM_INFO;
    uint64_t memUsage = 0;
    if (tag.hasMemInfo)
    {
        idx = ProfilerInlines::Read64(buff, idx, memUsage);
    }

    tag.cpuTime = cpuTime;
    tag.systemTime = (int64_t)systemTime;
    tag.memUsage = memUsage;
    return idx;
}

///////////////////////////////////////////////////////////////////////////
size_t Profiler::ReadEndTag(std::vector<uint8_t> &buff, size_t idx, Profiler::Tag &startTag)
{
    if (idx >= buff.size())
    {
        return idx;
    }

    timespec cpuTime;
    uint64_t systemTime;

    for(unsigned i = 0; i < sizeof(cpuTime); i++)
    {
        idx = ProfilerInlines::Read8(buff, idx, ((uint8_t*)&cpuTime)[i]);
    }

    idx = ProfilerInlines::Read64(buff, idx, systemTime);

    uint8_t hasMemInfoChar;
    idx = ProfilerInlines::Read8(buff, idx, hasMemInfoChar);
    bool hasMemInfo = hasMemInfoChar == PROFILER_MEM_INFO;
    if (hasMemInfo != startTag.hasMemInfo)
    {
        // Assert
    }

    uint64_t memUsage = 0;
    if (hasMemInfo)
    {
        idx = ProfilerInlines::Read64(buff, idx, memUsage);
    }

    startTag.cpuTime = ProfilerInlines::TimespecDiff(startTag.cpuTime, cpuTime);

    startTag.systemTime = systemTime - startTag.systemTime;
    if (startTag.hasMemInfo)
    {
        startTag.memUsage = memUsage - startTag.memUsage;
    }
    return idx;
}

///////////////////////////////////////////////////////////////////////////
//template< typename... Args > Profiler::BlockProfilingObject::BlockProfilingObject(Profiler &profiler,Args... args)

///////////////////////////////////////////////////////////////////////////
Profiler::BlockProfilingObject::~BlockProfilingObject()
{
    if (m_profilerStarted && (m_profiler != nullptr))
    {
        m_profiler->AddEndTag();
    }
}

#endif
