#ifndef __EGT_SYS_MODULE_MONITOR_H__
#define __EGT_SYS_MODULE_MONITOR_H__

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
#include <unordered_map>
#include <unordered_set>

#define EGT_MODULE_MONITOR(moduleName)      \
    egt::ModuleMonitor::ModuleMonitoringObject ____tmpModuleMonitoringgObj_(egt::ModuleMonitor::GetInstance(), moduleName);

//
#define EGT_MODULE_MONITOR_ADD_TAG(tagName, tagValue)           \
    {                                                           \
        auto __tmpMonitorA = egt::ModuleMonitor::GetInstance(); \
        if (nullptr != __tmpMonitorA)                           \
            __tmpMonitorA->AddTag(tagName, tagValue);           \
    }                                                           \

//
#define EGT_MODULE_MONITOR_REMOVE_TAG(tagName, tagValue)        \
    {                                                           \
        auto __tmpMonitorR = egt::ModuleMonitor::GetInstance(); \
        if (nullptr != __tmpMonitorR)                           \
            __tmpMonitorR->RemoveTag(tagName, tagValue);        \
    }                                                           \

//
#define EGT_MODULE_MONITOR_SAVE_SNAPSHOT(name) EGT_MODULE_MONITOR_ADD_TAG("_save_snapshot", name)

//

namespace egt {


class ModuleMonitor
{
public:

    class ModuleMonitoringObject
    {
    public:
        ModuleMonitoringObject(ModuleMonitor* monitor, const std::string& moduleName);
        ~ModuleMonitoringObject();

        ModuleMonitoringObject() = delete;
        ModuleMonitoringObject( const ModuleMonitoringObject& ) = delete;
        ModuleMonitoringObject( ModuleMonitoringObject& ) = delete;
        ModuleMonitoringObject( volatile const ModuleMonitoringObject& ) = delete;
        ModuleMonitoringObject( volatile ModuleMonitoringObject& ) = delete;
        ModuleMonitoringObject& operator=(ModuleMonitoringObject) = delete;
        ModuleMonitoringObject& operator=(ModuleMonitoringObject&& ) = delete;
        ModuleMonitoringObject& operator=(const ModuleMonitoringObject& ) = delete;

    private:
        ModuleMonitor* m_monitor;
        bool m_monitorStarted;
        int64_t systemStartTime;
        timespec cpuStartTime;
        int64_t startMemoryUsage;
        std::string moduleName;
        //
        int64_t cpuTimeUsedByOthers = 0;
        int64_t sysTimeUsedByOthers = 0;
        int64_t memoryUsedByOthers = 0;
        ModuleMonitoringObject* parent = nullptr;
    };


    struct ThreadContext
    {
        std::thread::id threadId{};
        ModuleMonitoringObject* lastObject = nullptr;
    };

    struct ModuleContext
    {
        std::string moduleName;
        int64_t memoryUsage = 0;
        int64_t systemTime = 0;
        int64_t cpuTime = 0;
        int64_t calls = 0;
    };

    struct MonitorContext
    {
        std::map<std::thread::id, ThreadContext> threads;
        std::unordered_map<std::string, ModuleContext> modules;
        timespec cpuTimeOnStart = {0, 0};
        bool isMultiThreaded = false;

        std::unordered_map<std::string, std::string> tags;
        std::mutex dataLocker;
    };

    virtual ~ModuleMonitor() = default;


    void StartMonitoring();
    bool IsStarted() const;
    void StopMonitoring();
    MonitorContext& GetContext();
    void AddTag(const std::string& tagName, const std::string& tagValue);
    void RemoveTag(const std::string& tagName);

    static ModuleMonitor* GetInstance();
    static void Init();
    static void Init(ModuleMonitor* monitor);
    static void Deinit();

private:
    ModuleMonitor();


    MonitorContext m_monitorContext;
    std::atomic_bool m_monitorStarted;


    static ModuleMonitor* s_monitorInstance;
    friend class ModuleMonitoringObject;
};

}

#endif // __EGT_SYS_MODULE_MONITOR_H__
