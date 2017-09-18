#include <thread>
#include <time.h>
#include <chrono>
#include <atomic>
//
#include <lib_utils/Profiler/Profiler.h>
#include <lib_utils/Network/Messengers/Messenger.h>
//
#include "ProfilerMgr.h"
#include "ProfilerMgrInterface.h"
#include <lib_utils/Profiler/Gl_Profiler.h>
namespace egt
{
namespace ProfilerMgr
{

static egt::Messenger<egt::NetMsg> m_net;
static std::atomic<bool> isStarted(false);
static std::thread worker;
static int connection = 0;
static bool shouldAutoStop = false;
static uint32_t maxProfilingTime = 0;

//////////////////////////////////////////////////////////////////
void StopProfiler()
{
    auto profilerPtr = egt::Profiler::GetInstance();
    if (nullptr == profilerPtr)
    {
        return;
    }
    auto& profiler = *profilerPtr;
    if (profiler.IsStarted() == false)
    {
        return;
    }

    profiler.StopProfiling();
    shouldAutoStop = false;
    maxProfilingTime = 0;

    SendData();
}

//////////////////////////////////////////////////////////////////
void IncommingMsg(egt::NetMsg& netMsg)
{
    auto profilerPtr = egt::Profiler::GetInstance();
    if (nullptr == profilerPtr)
    {
        return;
    }
    auto& profiler = *profilerPtr;
    //
    auto& buff = netMsg.payload;

    using namespace ProfilerInterface;
    switch (netMsg.id)
    {
    case MsgId::StartProfiling: // start
    {
        if (profiler.IsStarted())
        {
            break;
        }
        if (!buff.empty())
        {
            Config cfg;
            cfg.FromRaw(buff);
            shouldAutoStop = cfg.maxTimeMs > 0;
            maxProfilingTime = cfg.maxTimeMs;
            profiler.SetCpuProfilingDepth(cfg.cpuProfilingDepth);
#if defined(OLD_PROFILER_ON)
            profiler.SetMemProfilingDepth(cfg.memProfilingDepth);
#endif
            profiler.StartProfiling();
        }
    }
    break;
    case MsgId::EndProfiling:
    {
        StopProfiler();
    }
    break;

    case MsgId::GL_DataRequest:
    {
        NetMsg msg;
        msg.id = MsgId::GL_Data;
        DumpGlInfo(msg);
        m_net.SendMsg(connection, std::move(msg));
    }
    break;
    case MsgId::GL_StartCustomProfiling:
    {
        int id = netMsg.payload[0];
        egt::StartCustomGlProfiling(id);
    }
    break;
    case MsgId::GL_StopCustomProfiling:
    {
        int id = netMsg.payload[0];
        NetMsg msg;
        msg.id = MsgId::GL_CustomProfilingData;
        StopCustomGlProfiling(id, msg);
        m_net.SendMsg(connection, std::move(msg));
    }
    break;
    }
}

//////////////////////////////////////////////////////////////////
void ProfilerMgrWorker()
{
    while(isStarted)
    {
        if (shouldAutoStop == false)
        {
            m_net.ProcessBlocking();
        }
        else
        {
            m_net.ProcessBlocking(IConnection::Duration(maxProfilingTime));
            if (shouldAutoStop)
            {
                StopProfiler();
            }
        }
    }
}

void OnConnect(int connectionId)
{
    connection = connectionId;
}

void OnDisconnect(int)
{
    connection = 0;
}

void OnMsgRcv(int, egt::NetMsg& msg)
{
    IncommingMsg(msg);
}


//////////////////////////////////////////////////////////////////
void Start(IConnector::Ptr connector)
{
#if defined(EGT_CPU_PROFILING_ON) || defined(EGT_GPU_PROFILING_ON)
    if (isStarted == true)
    {
        return;
    }

    m_net.SetConnector( connector,
                        [](int connectionId){OnConnect(connectionId);},
                        [](int connectionId){OnDisconnect(connectionId);},
                        [](int connectionId, egt::NetMsg& msg){OnMsgRcv(connectionId, msg);},
                        nullptr);

    isStarted = true;
    worker = std::thread(ProfilerMgrWorker);
#endif
}

//////////////////////////////////////////////////////////////////
void Stop()
{
#if defined(EGT_CPU_PROFILING_ON) || defined(EGT_GPU_PROFILING_ON)
    isStarted = false;
    m_net.WakeUpProcess();
    if (worker.joinable()) worker.join();
#endif
}

void SendData()
{
    auto profilerPtr = egt::Profiler::GetInstance();
    if (nullptr == profilerPtr)
    {
        return;
    }
    auto& profiler = *profilerPtr;

    egt::NetMsg zoneMsg;
    zoneMsg.id = egt::ProfilerInterface::MsgId::ProfilingData;
#if defined(OLD_PROFILER_ON)
    zoneMsg.payload = profiler.DumpAndDestroyRawBuff();
#elif defined(NEW_PROFILER_ON)
    profiler.Serialize(zoneMsg.payload);
#endif
    m_net.SendMsg(connection, std::move(zoneMsg));
}

std::vector<uint8_t> GetRawGata()
{
    auto profilerPtr = egt::Profiler::GetInstance();
    if (nullptr == profilerPtr)
    {
        return {};
    }
    auto& profiler = *profilerPtr;

    std::vector<uint8_t> result;
#if defined(OLD_PROFILER_ON)
    result = profiler.DumpAndDestroyRawBuff();
#elif defined(NEW_PROFILER_ON)
    profiler.Serialize(result);
#endif
    return result;
}

}
}
