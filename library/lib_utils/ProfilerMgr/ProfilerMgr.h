#ifndef __EGT_PROFILER_MGR_H__
#define __EGT_PROFILER_MGR_H__

#include <lib_utils/Network/NetworkBase/IConnector.h>
#include <lib_utils/Profiler/Profiler.h>
#include <mutex>

// temp
#include "ModuleMonitorMgr.h"
namespace egt
{
namespace ProfilerMgr
{
    void Start(IConnector::Ptr connector);
    void Stop();
    void SendData();
    std::vector<uint8_t> GetRawGata();
}
}

#endif // __EGT_PROFILER_MGR_H__
