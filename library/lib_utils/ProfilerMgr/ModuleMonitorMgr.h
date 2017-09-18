#ifndef __EGT_MODULE_MONITOR_MGR_H__
#define __EGT_MODULE_MONITOR_MGR_H__

#include <lib_utils/Network/NetworkBase/IConnector.h>

namespace egt
{
namespace ModuleMonitorMgr
{
    void Start(IConnector::Ptr connector);
    void Stop();
}
}

#endif // __EGT_MODULE_MONITOR_MGR_H__
