#include "LocalClient.h"
#include <string.h>
#include <netdb.h>
#include "LocalConnection.h"
#include <sys/socket.h>
#include <unistd.h>
namespace egt{

//////////////////////////////////////////////////////////////////
LocalClient::LocalClient()
    : IConnector()
{
}

//////////////////////////////////////////////////////////////////
LocalClient::~LocalClient()
{
    _stop();
}

//////////////////////////////////////////////////////////////////
IConnection::Ptr LocalClient::_waitForConnection(Timepoint waitUntil)
{
    if (m_isRunning == false)
    {
        return nullptr;
    }
    auto connection = m_connection;
    if (connection == nullptr)
    {
        return _createConnection();
    }
    if (true == connection->WaitForDisconnectUntil(waitUntil))
    {
        return _createConnection();
    }

    return nullptr;
}

//////////////////////////////////////////////////////////////////
void LocalClient::_stop()
{
    m_isRunning = false;
    auto connection = m_connection;
    if (connection)
    {
        connection->Disconnect();
        m_connection = nullptr;
        _onNewEventCallback();
    }
}

IConnection::Ptr LocalClient::_createConnection()
{
    if (m_isRunning == false)
    {
        return nullptr;
    }
    auto server = m_server.lock();
    if (server == nullptr)
    {
        m_isRunning = false;
        _onNewEventCallback();
        return nullptr;
    }
    {
        std::lock_guard<std::mutex> lock(server->m_newClientLocker);

        auto clientConnection = std::make_shared<LocalConnection>();
        clientConnection->SetName("cl" + GetName());
        auto serverConnection = std::make_shared<LocalConnection>();
        serverConnection->SetName("sr" + GetName());

        clientConnection->id = 111;
        serverConnection->id = 222;

        m_connection = clientConnection;
        server->m_connections.push_back(serverConnection);

        clientConnection->Init(serverConnection);
        serverConnection->Init(clientConnection);
        LocalConnection::Start(clientConnection, serverConnection);
        server->m_newClientEvent.notify_all();
    }
    _onNewEventCallback();
    server->_onNewEventCallback();
    return m_connection;
}

//////////////////////////////////////////////////////////////////
void LocalClient::SetServer(std::weak_ptr<LocalServer> server)
{
    m_server = server;
}

//////////////////////////////////////////////////////////////////
void LocalClient::RunConnector()
{
    if (m_isRunning == true)
    {
        return;
    }
    m_isRunning = true;
}

}
