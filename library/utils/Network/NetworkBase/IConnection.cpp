//#include <sys/prctl.h>
//
#include <Platform.h>
//
#include "IConnection.h"

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

std::mutex IConnection::s_idLocker;
uint64_t IConnection::s_id = 1;


//////////////////////////////////////////////////////////////////////
void IConnection::_onNewEventCallback()
{
    std::unique_lock<std::mutex> locker(s_fnLocker);
    auto callback = m_newEventCallback;
    locker.unlock();

    if (nullptr != callback)
    {
        callback();
    }
}

//////////////////////////////////////////////////////////////////////
void IConnection::_setThreadName(std::thread& thread, const std::string &threadName)
{
    auto name = "_" + GetName() + "_" + threadName;
    Platform::Threads::ChangeName(thread, name);
}

//////////////////////////////////////////////////////////////////////
IConnection::IConnection()
{
    std::lock_guard<std::mutex> lock(s_idLocker);
    m_baseId = s_id;
    s_id++;
}

//////////////////////////////////////////////////////////////////////
IConnection::WaitResult IConnection::WaitForMsg(Duration timeout)
{
    return _waitForMsg( ::GetWaitTimepoint(timeout) );
}

//////////////////////////////////////////////////////////////////////
IConnection::WaitResult IConnection::WaitForMsgUntil(IConnection::Timepoint timepoint)
{
    return _waitForMsg( timepoint );
}

//////////////////////////////////////////////////////////////////////
IConnection::WaitResult IConnection::CheckForMsg()
{
    return WaitForMsg(Duration(0));
}

//////////////////////////////////////////////////////////////////////
IConnection::WaitResult IConnection::BlockForMsg()
{
    return WaitForMsg(Duration(-1));
}

//////////////////////////////////////////////////////////////////////
NetMsg IConnection::GetMsg()
{
    if (CheckForMsg() == WaitResult::NewMsg)
    {
        return _getMsg();
    }
    return NetMsg();
}

//////////////////////////////////////////////////////////////////////
bool IConnection::WaitForDisconnect(Duration timeout)
{
    return _waitForDisconnect(GetWaitTimepoint(timeout));
}

//////////////////////////////////////////////////////////////////////
bool IConnection::WaitForDisconnectUntil(IConnection::Timepoint timepoint)
{
    return _waitForDisconnect(timepoint);
}

//////////////////////////////////////////////////////////////////////
bool IConnection::CheckForDisconnect()
{
    return WaitForDisconnect(Duration(0));
}

//////////////////////////////////////////////////////////////////////
bool IConnection::BlockForDisconnect()
{
    return WaitForDisconnect(Duration(-1));
}

//////////////////////////////////////////////////////////////////////
IConnection::SendResult IConnection::SendMsg(NetMsg&& netMsg)
{
    return _sendMsg(std::move(netMsg));
}

//////////////////////////////////////////////////////////////////////
void IConnection::Disconnect()
{
    _disconnect();
}

//////////////////////////////////////////////////////////////////////
void IConnection::SetEventCallback(std::function<void ()> callback)
{
    std::lock_guard<std::mutex> locker(s_fnLocker);
    m_newEventCallback = callback;
}

//////////////////////////////////////////////////////////////////////
std::string IConnection::GetName() const
{
    std::lock_guard<std::mutex> lock(s_idLocker);
    return m_name;
}

//////////////////////////////////////////////////////////////////////
void IConnection::SetName(const std::string &name)
{
    std::lock_guard<std::mutex> lock(s_idLocker);
    m_name = name;
}

}
