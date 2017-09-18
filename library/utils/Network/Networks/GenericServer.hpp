namespace egt{

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
GenericServer<SocketImpl>::GenericServer()
    : IConnector()
{
    m_socket = std::make_shared<SocketImpl>();
    m_isRunning = false;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
GenericServer<SocketImpl>::~GenericServer()
{
    Stop();
    if (m_connectorThread.joinable()) m_connectorThread.join();
    m_socket->CloseSocket();
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
IConnection::Ptr GenericServer<SocketImpl>::_waitForConnection(Timepoint waitUntil)
{
    std::unique_lock<std::mutex> lock(m_locker);
    if (m_connection != nullptr)
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
        ret = m_newConnectionEvent.wait_until(lock, waitUntil);
        if (m_connection != nullptr)
        {
            return _returnActiveConnection();
        }
    }
    return _returnActiveConnection();
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericServer<SocketImpl>::_stop()
{
    std::lock_guard<std::mutex> lock(m_locker);
    if (m_isRunning == false)
    {
        return;
    }
    m_isRunning = false;
    m_socket->ShutdownSocket();
    m_newConnectionEvent.notify_all();
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericServer<SocketImpl>::SetServerInfo(typename SocketImpl::ServerConfig cfg)
{
    m_cfg = cfg;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericServer<SocketImpl>::RunConnector()
{
    if (m_isRunning == true)
    {
        return;
    }
    m_isRunning = true;
    m_connectorThread = std::thread([this](){ _serverLoop(); });
    _setThreadName(m_connectorThread, "srvLp");
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericServer<SocketImpl>::_serverLoop()
{
    while(1)
    {
        if (m_isRunning == false)
        {
            m_socket->ShutdownSocket();
            return;
        }
        _createServer();
        _acceptConnections();
    }
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
IConnection::Ptr GenericServer<SocketImpl>::_returnActiveConnection()
{
    auto res = m_connection;
    m_connection = nullptr;
    if (res != nullptr)
    {
        bool isLocked = m_locker.try_lock();
        m_newConnectionEvent.notify_all();
        if (isLocked)
        {
            m_locker.unlock();
        }
    }
    return res;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericServer<SocketImpl>::_createServer()
{
    if (m_isRunning == false)
    {
        return;
    }
    while(1)
    {
        _sleep();

        if (m_isRunning == false)
        {
            return;
        }

        if (true == m_socket->CreateServer(m_cfg, 16))
        {
            return;
        }
    }
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericServer<SocketImpl>::_acceptConnections()
{
    if (m_isRunning == false)
    {
        return;
    }

    while(1)
    {
        if (m_isRunning == false)
        {
            return;
        }

        auto newConnectionSocket = std::make_shared<SocketImpl>();
        if ( false == m_socket->Listen(*newConnectionSocket))
        {
            return;
        }

        auto newConnection = std::make_shared<Connection>();
        newConnection->SetName(GetName());
        newConnection->Start(newConnectionSocket);
        std::unique_lock<std::mutex> lock(m_locker);
        while((m_connection != nullptr) && (m_isRunning == true))
        {
            m_newConnectionEvent.wait(lock);
        }
        if ((m_connection == nullptr) && (m_isRunning == true))
        {
            m_connection = newConnection;
            m_newConnectionEvent.notify_all();
        }
        else
        {
            newConnection->Disconnect();
            newConnection = nullptr;
        }
        lock.unlock();
        _onNewEventCallback();
    }
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericServer<SocketImpl>::_sleep()
{
    if (m_isRunning == false)
    {
        return;
    }

    std::unique_lock<std::mutex> lock(m_locker);
    auto waitUntil = std::chrono::system_clock::now() + std::chrono::milliseconds(500);
    std::cv_status ret = std::cv_status::no_timeout;
    while(ret != std::cv_status::timeout)
    {
        if (m_isRunning == false)
        {
            return;
        }
        ret = m_newConnectionEvent.wait_until(lock, waitUntil);
    }
}

}
