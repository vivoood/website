#include <thread>
#include <time.h>
#include <chrono>
#include <atomic>
#include <mutex>
//
#include <lib_utils/Network/Messengers/Messenger.h>
#include <lib_utils/GenericMsg/GenericMsg.h>
#include <lib_utils/UniStream/UniStream.h>
#include <lib_utils/Profiler/ModuleMonitor.h>
#include <lib_utils/Crc.h>
//
#include "ModuleMonitorMgr.h"
#include "ProfilerMgrInterface.h"
#include <sstream>
#include "ProfilerMgr.h"

namespace egt
{
namespace ModuleMonitorMgr
{

inline int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

inline int64_t GetMemoryUsage()
{
    static pid_t pId = getpid();
    static std::string procName;
    if (procName.empty())
    {
        std::stringstream ss;
        ss << "/proc/";
        ss << pId;
        ss << "/status";
        procName = ss.str();
    }

    FILE* file = fopen(procName.c_str(), "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);

    return result;
}


static int64_t s_memUsage = 0;
static int64_t s_cpuTimeMicros = 0;
using Msg = egt::GenericMsg<egt::oUniStream, egt::iUniStream>;

static egt::Messenger<Msg> m_net;
static std::atomic<bool> isStarted(false);
static std::thread worker;
static std::chrono::milliseconds updateFrequency = std::chrono::milliseconds(1000);
static std::set<int> s_connections;
//
void DumpMsgFromMonitor(Msg& msg)
{
    auto inst = ModuleMonitor::GetInstance();
    if (nullptr == inst)
    {
        return;
    }
    auto& context = inst->GetContext();

    std::unique_lock<std::mutex> locker(context.dataLocker);
        // take whatever you want
        auto modules = context.modules;
        auto tags = context.tags;
        context.tags.erase("_save_snapshot");
    locker.unlock();

    int64_t memUsage = GetMemoryUsage();
    timespec cpuTime;
    ProfilerInlines::GetProcessCpuTime(cpuTime);
    int64_t cpuUsage = ProfilerInlines::TimespecDiffInMicro(context.cpuTimeOnStart, cpuTime);

    std::vector<Msg> modulesMsg;
    for (const auto& p : modules)
    {
        const auto& moduleName = p.first;
        const auto& moduleStat = p.second;
        modulesMsg.emplace_back(Msg());
        Msg& moduleMsg = modulesMsg.back();
        moduleMsg.name = moduleName;
        moduleMsg.AddValue("cpu_time", moduleStat.cpuTime);
        moduleMsg.AddValue("sys_time", moduleStat.systemTime);
        moduleMsg.AddValue("mem_usage", moduleStat.memoryUsage);
        moduleMsg.AddValue("calls", moduleStat.calls);
    }

    msg.AddValue("modules", modulesMsg);
    msg.AddValue("mem_usage", memUsage);
    msg.AddValue("cpu_time", cpuUsage);
    msg.AddValue("tags", tags);
}

void SendMsg(Msg& msg)
{
    for (auto connection : s_connections)
    {
        m_net.SendMsg(connection, Msg(msg));
    }
}

//////////////////////////////////////////////////////////////////
void MonitorMgrWorker()
{
    while(isStarted)
    {
        {
            m_net.ProcessBlocking(IConnection::Duration(updateFrequency));
            if (true == s_connections.empty())
            {
                continue;
            }

            auto monitorPtr = egt::ModuleMonitor::GetInstance();
            if (nullptr == monitorPtr)
            {
                return;
            }
            auto& monitor = *monitorPtr;
            if (monitor.IsStarted() == false)
            {
                continue;
            }
            Msg msg;
            DumpMsgFromMonitor(msg);
            msg.name = "snapshot_update";
            SendMsg(msg);
        }
    }
    return;
}

void SendStatus()
{
    if (true == s_connections.empty())
    {
        return;
    }

    bool isMonitoring = false;
    auto* monitor = egt::ModuleMonitor::GetInstance();
    if (nullptr != monitor)
    {
        isMonitoring = monitor->IsStarted();
    }
    //
    if (true == isMonitoring)
    {
        Msg response;
        response.name = "monitoring_started";
        response.AddValue("memory_usage_at_start", s_memUsage);
        response.AddValue("cpu_time_at_start", s_cpuTimeMicros);
        SendMsg(response);
    }
    else
    {
        Msg response;
        response.name = "monitoring_stopped";
        SendMsg(response);
    }
}

void OnConnect(int connectionId)
{
    s_connections.insert(connectionId);
    SendStatus();
}

void OnDisconnect(int connectionId)
{
    s_connections.erase(connectionId);
}

void OnMsgRcv(int, Msg& msg)
{
    auto monitorPtr = egt::ModuleMonitor::GetInstance();
    if (nullptr == monitorPtr)
    {
        return;
    }
    auto& monitor = *monitorPtr;

    switch (CRC::Hash(msg.name.c_str()))
    {
        case CRC::Hash("start_monitoring"):
        {
            monitor.StartMonitoring();
            //
            s_memUsage = static_cast<int64_t>(ProfilerInlines::GetMemoryUsage());
            timespec timeZero = {0, 0};
            timespec cpuTimespec = {0, 0};
            ProfilerInlines::GetProcessCpuTime(cpuTimespec);
            s_cpuTimeMicros = ProfilerInlines::TimespecDiffInMicro(timeZero, cpuTimespec);

            Profiler::GetInstance()->StartProfiling();
            SendStatus();
        }
        break;
        case CRC::Hash("stop_monitoring"):
        {
            monitor.StopMonitoring();

            SendStatus();
        }
        break;
        case CRC::Hash("new_frequency"):
        {
            int64_t newFrequency = 1000;
            if ( msg.GetValue("frequency", newFrequency) )
            {
                updateFrequency = std::chrono::milliseconds(newFrequency);
            }
        }
        break;
        case CRC::Hash("take_memory"):
        {
            static std::vector<uint8_t> fakeLeak;
            static uint8_t c = 0;
            fakeLeak.resize( fakeLeak.size() + 4 * 1024 * 1024 );
            c++;
            for(auto& b : fakeLeak) b = c;
//            for (size_t i = 0; i < 16; i++)
//            {
//                fakeLeak[(fakeLeak.size() / (16)) * i] = c;
//            }

        }
        break;
        case CRC::Hash("get_profiler_data"):
        {
            auto rawBuff = ::egt::ProfilerMgr::GetRawGata();
            if (true == rawBuff.empty())
            {
                return;
            }
            Msg reply;
            reply.name = "profiler_data";
            reply.AddValue("profile_data", rawBuff);
            Msg memento;
            if (msg.GetValue("memento", memento))
            {
                reply.AddValue("memento", memento);
            }
            SendMsg(reply);
        }
        break;
        //
        default:break;
    }
}

//////////////////////////////////////////////////////////////////
void Start(IConnector::Ptr connector)
{
    if (isStarted == true)
    {
        return;
    }

    m_net.SetConnector( connector,
                        [](int connectionId){OnConnect(connectionId);},
                        [](int connectionId){OnDisconnect(connectionId);},
                        [](int connectionId, Msg& msg){OnMsgRcv(connectionId, msg);},
                        nullptr);

    isStarted = true;
    worker = std::thread(MonitorMgrWorker);
}

//////////////////////////////////////////////////////////////////
void Stop()
{
    isStarted = false;
    m_net.WakeUpProcess();
    if (worker.joinable())
    {
        worker.join();
    }
}

}
}
