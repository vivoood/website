
namespace egt{

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
GenericClient<SocketImpl>::GenericClient()
    : IConnector()
{
    m_socket = std::make_shared<SocketImpl>();
    m_isNew = false;
    m_isRunning = false;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
GenericClient<SocketImpl>::~GenericClient()
{
    Stop();
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
IConnection::Ptr GenericClient<SocketImpl>::_waitForConnection(Timepoint waitUntil)
{
    std::unique_lock<std::mutex> lock(m_locker);

    {
        auto connection = m_connection;
        if (connection != nullptr && m_isNew == true)
        {
            return _returnActiveConnection();
        }
    }

    std::cv_status ret = std::cv_status::no_timeout;
    while(ret != std::cv_status::timeout)
    {
        if (m_isRunning == false)
        {
            return _returnActiveConnection();
        }
        ret = m_newConnectionEvent.wait_until(lock, waitUntil);
        {
            auto connection = m_connection;
            if (connection != nullptr)
            {
                return _returnActiveConnection();
            }
        }
    }
    return _returnActiveConnection();
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericClient<SocketImpl>::_stop()
{
    m_locker.lock();
    try {
        m_isRunning = false;
        {
            auto connection = m_connection;
            if (connection != nullptr)
            {
                connection->Disconnect();
                _resetConnectionPointer();
            }
        }
        m_newConnectionEvent.notify_all();
    } catch (...) {}
    m_locker.unlock();

    if (m_connectorThread.joinable())
    {
        m_connectorThread.join();
    }
    m_socket->CloseSocket();
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericClient<SocketImpl>::SetServerInfo(const typename SocketImpl::ServerAddress& address)
{
    m_serverAddress = address;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericClient<SocketImpl>::RunConnector()
{
    if (m_isRunning == true)
    {
        return;
    }
    m_isRunning = true;
    m_connectorThread = std::thread([this](){ _connectorLoop(); });
    _setThreadName(m_connectorThread, "Lp");
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericClient<SocketImpl>::_connectorLoop()
{
    {
        auto connection = m_connection;
        if (connection)
        {
            connection->Disconnect();
            _resetConnectionPointer();
        }
    }

    while(1)
    {
        if (m_isRunning == false)
        {
            return;
        }
        _sleep();
        if (m_socket->CreateClient(m_serverAddress) == false)
        {
            continue;
        }
        if (m_socket->ConnectToServer() == false)
        {
            m_socket->ShutdownSocket();
            m_socket->CloseSocket();
            continue;
        }

        m_locker.lock();
        try
        {
            m_connection = std::make_shared<Connection>();
            m_connection->SetName(GetName());
            m_connection->Start(m_socket);
            m_isNew = true;
            if (m_isRunning == true)
            {
                m_newConnectionEvent.notify_all();
            }
            else
            {
                {
                    auto connection = m_connection;
                    if (nullptr != connection)
                    {
                        m_connection->Disconnect();
                        _resetConnectionPointer();
                    }
                }
            }
        } catch (...) {}
        m_locker.unlock();
        _onNewEventCallback();
        {
            auto connection = m_connection;
            if (connection != nullptr)
            {
                connection->BlockForDisconnect( );
                _resetConnectionPointer();
            }
        }
    }
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
IConnection::Ptr GenericClient<SocketImpl>::_returnActiveConnection()
{
    if (m_isNew == false)
    {
        return nullptr;
    }

    m_isNew = false;
    return m_connection;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericClient<SocketImpl>::_sleep()
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

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericClient<SocketImpl>::_resetConnectionPointer()
{
    std::lock_guard<std::mutex> locker(m_resetConnectionLocker);
    m_connection.reset();
}

}
