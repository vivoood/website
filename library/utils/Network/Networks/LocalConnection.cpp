#include <unistd.h>
#include "LocalConnection.h"
#include <sys/socket.h>

///////////////////////////////////////////////////////////////////////////

namespace egt{

//////////////////////////////////////////////////////////////////
LocalConnection::LocalConnection()
    : IConnection()
{
}

//////////////////////////////////////////////////////////////////
LocalConnection::~LocalConnection()
{
    _disconnect();
}

//////////////////////////////////////////////////////////////////
void LocalConnection::Init(std::weak_ptr<LocalConnection> remote)
{
    m_remote = remote;
}

//////////////////////////////////////////////////////////////////
void LocalConnection::Start(std::shared_ptr<LocalConnection> c1, std::shared_ptr<LocalConnection> c2)
{
    c1->m_isConnected = true;
    c2->m_isConnected = true;

    c1->_startNotifier();
    c2->_startNotifier();
}

//////////////////////////////////////////////////////////////////
IConnection::WaitResult LocalConnection::_waitForMsg(Timepoint waitUntil)
{
    auto remote = m_remote.lock();
    if ((remote == nullptr) || (m_isConnected == false))
    {
        m_isConnected = false;
        return IConnection::WaitResult::Disconnected;
    }
    std::unique_lock<std::mutex> lock(m_lockerIn);
    remote = nullptr; // release it after m_lockerIn lock

    if (m_incomming.empty() == false)
    {
        return IConnection::WaitResult::NewMsg;
    }

    std::cv_status ret = std::cv_status::no_timeout;

    while(ret != std::cv_status::timeout)
    {
        ret = m_inEvent.wait_until(lock, waitUntil);
        if (m_incomming.empty() == false)
        {
            return IConnection::WaitResult::NewMsg;
        }
        if (m_remote.lock() == nullptr || m_isConnected == false)
        {
            m_isConnected = false;
            return IConnection::WaitResult::Disconnected;
        }
    }
    return IConnection::WaitResult::NoMsg;
}

//////////////////////////////////////////////////////////////////
NetMsg LocalConnection::_getMsg()
{
    std::lock_guard<std::mutex> lock(m_lockerIn);

    if (m_incomming.empty() == true)
    {
        return NetMsg();
    }
    auto msg = std::move(m_incomming.front());
    m_incomming.pop();
    return msg;
}

//////////////////////////////////////////////////////////////////
IConnection::SendResult LocalConnection::_sendMsg(NetMsg&& netMsg)
{
    auto remote = m_remote.lock();
    if (remote == nullptr || m_isConnected == false)
    {
        m_isConnected = false;
        return IConnection::SendResult::Disconnected;
    }
    {
        std::lock_guard<std::mutex> lock(remote->m_lockerIn);
        remote->m_incomming.emplace(netMsg);
        remote->m_inEvent.notify_all();
    }
    _notifyRemoteConnection();
    return IConnection::SendResult::SendOk;
}

bool LocalConnection::_waitForDisconnect(Timepoint waitUntil)
{
    auto remote = m_remote.lock();
    if ((remote == nullptr) || (m_isConnected == false))
    {
        m_isConnected = false;
        return true;
    }
    std::unique_lock<std::mutex> lock(m_lockerDisconnect);
    remote = nullptr; // release it after m_lockerDisconnect lock
    std::cv_status ret = std::cv_status::no_timeout;

    while(ret != std::cv_status::timeout)
    {
        ret = m_disconnectEvent.wait_until(lock, waitUntil);
        if (m_remote.lock() == nullptr || m_isConnected == false)
        {
            m_isConnected = false;
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////
void LocalConnection::_disconnect()
{
    if (m_isConnected == false)
    {
        return;
    }
    m_isConnected = false;
    {
        std::lock_guard<std::mutex> lockIn(m_lockerIn);
        m_inEvent.notify_all();
    }
    {
        std::lock_guard<std::mutex> lockDisconnect(m_lockerDisconnect);
        m_disconnectEvent.notify_all();
    }

    if (m_remoteNotificator.joinable())
    {
        {
            std::lock_guard<std::mutex> locker(m_removeNotificatorLocker);
            m_shouldExit = true;
            m_removeNotificatorEvent.notify_all();
        }
        m_remoteNotificator.join();
    }

    auto remote = m_remote.lock();
    if (remote)
    {
        remote->_disconnect();
    }
}

void LocalConnection::_startNotifier()
{
    m_shouldNotify = false;
    m_shouldExit = false;
    m_remoteNotificator = std::thread([this](){_remoteNotificatorLoop();});
}

void LocalConnection::_notifyRemoteConnection()
{
    std::lock_guard<std::mutex> locker(m_removeNotificatorLocker);
    m_shouldNotify = true;
    m_removeNotificatorEvent.notify_all();
}

void LocalConnection::_remoteNotificatorLoop()
{
    std::unique_lock<std::mutex> locker(m_removeNotificatorLocker);
    while(true)
    {
        if (m_shouldExit)
        {
            return;
        }
        if (m_shouldNotify)
        {
            m_shouldNotify = false;
            locker.unlock();
            auto remote = m_remote.lock();
            if (remote == nullptr)
            {
                return;
            }
            else
            {
                remote->_onNewEventCallback();
            }
            locker.lock();
        }
        m_removeNotificatorEvent.wait(locker);
    }
}


}
