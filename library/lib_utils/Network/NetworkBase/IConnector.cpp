#include <sys/prctl.h>
//
#include <lib_utils/Platform/Platform.h>
//
#include "IConnector.h"

namespace
{
//////////////////////////////////////////////////////////////////////
std::chrono::system_clock::time_point GetWaitTimepoint(egt::IConnection::Duration timeout)
{
    if(timeout < egt::IConnection::Duration(0))
    {
       return std::chrono::system_clock::time_point::max();
    }
    else
    {
        return std::chrono::system_clock::now() + timeout;
    }
}
}

namespace egt
{

std::mutex IConnector::s_idLocker;
uint64_t IConnector::s_id = 1;

//////////////////////////////////////////////////////////////////////
IConnector::IConnector()
{
    std::lock_guard<std::mutex> lock(s_idLocker);
    m_baseId = s_id;
    s_id++;
}

//////////////////////////////////////////////////////////////////////
void IConnector::_onNewEventCallback()
{
    if (nullptr != m_newEventCallback)
    {
        m_newEventCallback();
    }
}

//////////////////////////////////////////////////////////////////////
IConnection::Ptr IConnector::WaitForConnection(Duration timeout)
{
    return _waitForConnection(::GetWaitTimepoint(timeout));
}

//////////////////////////////////////////////////////////////////////
IConnection::Ptr IConnector::CheckForConnection()
{
    return WaitForConnection(Duration(0));
}

//////////////////////////////////////////////////////////////////////
IConnection::Ptr IConnector::BlockForConnection()
{
    return WaitForConnection(Duration(-1));
}

//////////////////////////////////////////////////////////////////////
void IConnector::SetEventCallback(std::function<void ()> callback)
{
    m_newEventCallback = callback;
}

//////////////////////////////////////////////////////////////////////
void IConnector::Stop()
{
    _stop();
}

//////////////////////////////////////////////////////////////////////
std::string IConnector::GetName() const
{
    std::lock_guard<std::mutex> lock(s_idLocker);
    return m_name;
}

//////////////////////////////////////////////////////////////////////
void IConnector::SetName(const std::string &name)
{
    std::lock_guard<std::mutex> lock(s_idLocker);
    m_name = name;
}

//////////////////////////////////////////////////////////////////////
void IConnector::_setThreadName(std::thread& thread, const std::string &threadName)
{
    auto name = GetName() + "_" + threadName;
    Platform::Threads::ChangeName(thread, name);
}

}
