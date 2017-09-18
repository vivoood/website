#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>

#include "LocalConnection.h"
#include "LocalServer.h"

namespace egt{

//////////////////////////////////////////////////////////////////
LocalServer::LocalServer()
    : IConnector()
{
    m_isRunning = false;
}

//////////////////////////////////////////////////////////////////
LocalServer::~LocalServer()
{
    Stop();
}

//////////////////////////////////////////////////////////////////
IConnection::Ptr LocalServer::_waitForConnection(Timepoint waitUntil)
{
    std::unique_lock<std::mutex> lock(m_newClientLocker);
    if (m_connections.empty() == false)
    {
        return _returnActiveConnection();
    }
    std::cv_status ret = std::cv_status::no_timeout;
    while(ret != std::cv_status::timeout)
    {
        if (m_isRunning == false)
        {
            return _returnActiveConnection();
        }
        ret = m_newClientEvent.wait_until(lock, waitUntil);
        if (m_connections.empty() == false)
        {
            return _returnActiveConnection();
        }
    }
    return _returnActiveConnection();
}

//////////////////////////////////////////////////////////////////
void LocalServer::_stop()
{
    std::lock_guard<std::mutex> lock(m_newClientLocker);
    if (m_isRunning == false)
    {
        return;
    }
    m_isRunning = false;
    m_newClientEvent.notify_all();
}

//////////////////////////////////////////////////////////////////
IConnection::Ptr LocalServer::_returnActiveConnection()
{
    if (m_connections.empty())
    {
        return nullptr;
    }
    auto result = m_connections[0];
    m_connections.erase(m_connections.begin(), m_connections.begin()+ 1);
    return result;
}

//////////////////////////////////////////////////////////////////
void LocalServer::RunConnector()
{
    if (m_isRunning == true)
    {
        return;
    }
    m_isRunning = true;
}

}
