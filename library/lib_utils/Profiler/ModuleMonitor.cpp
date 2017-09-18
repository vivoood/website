#include "ModuleMonitor.h"
#include <time.h>
#include <chrono>
#include "ProfilerInlines.h"
#include <sstream>
using namespace egt;


ModuleMonitor* ModuleMonitor::s_monitorInstance = nullptr;


namespace monitor_tools
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
}



///////////////////////////////////////////////////////////////////////////
ModuleMonitor::ModuleMonitoringObject::~ModuleMonitoringObject()
{
    if (false == m_monitorStarted || (nullptr == m_monitor))
    {
        return;
    }

    int64_t systemEndTime = ProfilerInlines::GetMonotonicMicro();
    timespec cpuEndTime = {0, 0};
    ProfilerInlines::GetThreadCpuTime(cpuEndTime);
    int64_t endMemoryUsage = monitor_tools::GetMemoryUsage();

    int64_t cpuDuration = ProfilerInlines::TimespecDiffInMicro(cpuStartTime, cpuEndTime);
    int64_t sysDuration = systemEndTime - systemStartTime;
    int64_t memUsage = endMemoryUsage - startMemoryUsage;

    auto& context = m_monitor->m_monitorContext;
    std::lock_guard<std::mutex> locker(context.dataLocker);
    auto& threadContext = context.threads[std::this_thread::get_id()];
    auto& moduleContext = context.modules[moduleName];

    if (nullptr != parent)
    {
        parent->cpuTimeUsedByOthers += cpuDuration;
        parent->sysTimeUsedByOthers += sysDuration;
        parent->memoryUsedByOthers += memUsage;
        threadContext.lastObject = parent;
    }
    else
    {
        if (context.threads.size() > 1)
        {
            context.isMultiThreaded = true;
        }
        context.threads.erase(std::this_thread::get_id());
    }

    cpuDuration -= cpuTimeUsedByOthers;
    sysDuration -= sysTimeUsedByOthers;
    memUsage -= memoryUsedByOthers;

    moduleContext.cpuTime += cpuDuration;
    moduleContext.systemTime += sysDuration;
    moduleContext.memoryUsage += memUsage;
    moduleContext.calls++;
}

egt::ModuleMonitor::ModuleMonitoringObject::ModuleMonitoringObject(egt::ModuleMonitor *monitor, const std::string &moduleName)
    : m_monitor(monitor)
    , m_monitorStarted( (monitor == nullptr) ? false : monitor->m_monitorStarted.load() )
    , systemStartTime(0)
    , cpuStartTime()
    , startMemoryUsage(0)
    , moduleName(moduleName)
{
    if (false == m_monitorStarted)
    {
        return;
    }

    ProfilerInlines::GetThreadCpuTime(cpuStartTime);
    systemStartTime = ProfilerInlines::GetMonotonicMicro();
    startMemoryUsage = monitor_tools::GetMemoryUsage();

    auto& context = m_monitor->m_monitorContext;
    std::lock_guard<std::mutex> locker(context.dataLocker);
    auto& threadContext = context.threads[std::this_thread::get_id()];
    parent = threadContext.lastObject;
    threadContext.lastObject = this;
}


void ModuleMonitor::StartMonitoring()
{
    if (true == IsStarted())
    {
        return;
    }
    std::lock_guard<std::mutex> locker(m_monitorContext.dataLocker);

    ProfilerInlines::GetThreadCpuTime(m_monitorContext.cpuTimeOnStart);
    m_monitorContext.isMultiThreaded = false;
    m_monitorContext.threads.clear();
    m_monitorContext.modules.clear();
    m_monitorStarted.store(true);
}

bool ModuleMonitor::IsStarted() const
{
    return  m_monitorStarted.load();
}

void ModuleMonitor::StopMonitoring()
{
    m_monitorStarted.store(false);
}

ModuleMonitor::MonitorContext &ModuleMonitor::GetContext()
{
    return m_monitorContext;
}

void ModuleMonitor::AddTag(const std::string& tagName, const std::string& tagValue)
{
    if (false == IsStarted())
    {
        return;
    }
    std::lock_guard<std::mutex> locker(m_monitorContext.dataLocker);
    m_monitorContext.tags[tagName] = tagValue;
}

void ModuleMonitor::RemoveTag(const std::string &tag)
{
    if (false == IsStarted())
    {
        return;
    }
    std::lock_guard<std::mutex> locker(m_monitorContext.dataLocker);
    m_monitorContext.tags.erase(tag);
}

ModuleMonitor *ModuleMonitor::GetInstance()
{
    return s_monitorInstance;
}

void ModuleMonitor::Init()
{
    if (nullptr == s_monitorInstance)
    {
        s_monitorInstance = new ModuleMonitor();
    }
}

void ModuleMonitor::Init(ModuleMonitor *monitor)
{
    if (nullptr == s_monitorInstance)
    {
        s_monitorInstance = monitor;
    }
}

void ModuleMonitor::Deinit()
{
    if (nullptr == s_monitorInstance)
    {
        delete s_monitorInstance;
        s_monitorInstance = nullptr;
    }
}

ModuleMonitor::ModuleMonitor()
    : m_monitorStarted(false)
{

}
