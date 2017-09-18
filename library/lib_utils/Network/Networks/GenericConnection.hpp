
namespace egt{

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
GenericConnection<SocketImpl>::GenericConnection()
    : IConnection()
{
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
GenericConnection<SocketImpl>::~GenericConnection()
{
    _disconnect();
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericConnection<SocketImpl>::Start(std::shared_ptr<SocketImpl> socketImpl)
{
    m_socket = socketImpl;
    if (_isSocketValid() == false)
    {
        return;
    }
    if (SocketImpl::CanRead())
    {
        m_reader = std::thread([this](){_readerLoop();});
        _setThreadName(m_reader, "rLp");
    }
    if (SocketImpl::CanWrite())
    {
        m_writer = std::thread([this](){_writerLoop();});
        _setThreadName(m_writer, "wLp");
    }
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
IConnection::WaitResult GenericConnection<SocketImpl>::_waitForMsg(Timepoint waitUntil)
{
    if (_isSocketValid() == false)
    {
        return IConnection::WaitResult::Disconnected;
    }

    std::unique_lock<std::mutex> lock(m_lockerIn);

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
        if (_isSocketValid() == false)
        {
            return IConnection::WaitResult::Disconnected;
        }
    }
    return IConnection::WaitResult::NoMsg;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
NetMsg GenericConnection<SocketImpl>::_getMsg()
{
    std::unique_lock<std::mutex> lock(m_lockerIn);

    if (m_incomming.empty() == true)
    {
        return NetMsg();
    }
    auto msg = std::move(m_incomming.front());
    m_incomming.pop();
    return msg;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
IConnection::SendResult GenericConnection<SocketImpl>::_sendMsg(NetMsg&& netMsg)
{
    if (_isSocketValid() == false)
    {
        return IConnection::SendResult::Disconnected;
    }
    if (SocketImpl::CanWrite() == false)
    {
        return IConnection::SendResult::Error;
    }
    std::unique_lock<std::mutex> lock(m_lockerOut);
    m_outgoing.emplace(netMsg);
    m_outEvent.notify_all();
    return IConnection::SendResult::SendOk;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
bool GenericConnection<SocketImpl>::_waitForDisconnect(Timepoint waitUntil)
{
    std::unique_lock<std::mutex> lock(m_lockerDisconnect);
    if (_isSocketValid() == false)
    {
        return true;
    }

    std::cv_status ret = std::cv_status::no_timeout;

    while(ret != std::cv_status::timeout)
    {
        ret = m_disconnectEvent.wait_until(lock, waitUntil);
        if (_isSocketValid() == false)
        {
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericConnection<SocketImpl>::_disconnect()
{
    if (_isSocketValid())
    {
        _shutdownConnection();
    }
    try
    {
        m_outEvent.notify_all();
        if (m_reader.joinable()) m_reader.join();
        if (m_writer.joinable()) m_writer.join();
    }
    catch (...)
    {}
    std::lock_guard<std::mutex> locker(m_lockerDisconnect);
    auto socket = m_socket;
    if (nullptr != socket)
    {
        socket->CloseSocket();
    }
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericConnection<SocketImpl>::_shutdownConnection()
{
    m_lockerDisconnect.lock();
    try
    {
        auto socket = m_socket;
        if (nullptr != socket)
        {
            socket->ShutdownSocket();
        }
    } catch (...) {}
    m_disconnectEvent.notify_all();
    m_lockerDisconnect.unlock();
    {
        std::lock_guard<std::mutex> lock(m_lockerIn);
        m_inEvent.notify_all();
    }
    {
        std::lock_guard<std::mutex> lock(m_lockerOut);
        m_outEvent.notify_all();
    }
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericConnection<SocketImpl>::_readerLoop()
{
    while( _isSocketValid() )
    {
        NetMsg::HeaderSize headerSz = 0;
        std::vector<uint8_t> rawMsg;
        {
            auto socket = m_socket;
            if (nullptr != socket)
            {
                if (false == socket->Peek(&headerSz, 1))
                {
                    break;
                }
                rawMsg.resize(headerSz);
                if (false == socket->Peek(rawMsg.data(), rawMsg.size()))
                {
                    break;
                }
                auto header = NetMsg::DeserializeHeader(rawMsg.data());

                rawMsg.resize( header.headerSize + header.payloadSize );
                if (false == socket->Read(rawMsg.data(), rawMsg.size() ) )
                {
                    break;
                }
            }
        }

        NetMsg msg = NetMsg::Deserialize(std::move(rawMsg));
        {
            std::lock_guard<std::mutex> lock(m_lockerIn);
            m_incomming.emplace(std::move(msg));
            m_inEvent.notify_all();
        }
        _onNewEventCallback();
    }
    if (_isSocketValid())
    {
        _shutdownConnection();
    }
    _onNewEventCallback();
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
void GenericConnection<SocketImpl>::_writerLoop()
{
    // writer thread
    std::unique_lock<std::mutex> lock(m_lockerOut);
    while(1)
    {
        while (m_outgoing.empty())
        {
            if (_isSocketValid() == false)
            {
                return;
            }
            m_outEvent.wait(lock);
        }

        while(false == m_outgoing.empty())
        {
            if (_isSocketValid() == false)
            {
                return;
            }

            NetMsg msg = std::move(m_outgoing.front());
            m_outgoing.pop();
            lock.unlock();
            // send it
            if (_isSocketValid())
            {
                auto raw = NetMsg::Serialize(std::move(msg));
                auto socket = m_socket;
                if (nullptr != socket)
                {
                    if( false == socket->Write(raw.data(), raw.size()))
                    {
                        if (_isSocketValid())
                        {
                            _shutdownConnection();
                        }
                        return;
                    }
                }
            }
            lock.lock();
        }
    }
}

//////////////////////////////////////////////////////////////////
template<typename SocketImpl>
bool GenericConnection<SocketImpl>::_isSocketValid() const
{
    auto socket = m_socket;
    if (socket == nullptr)
    {
        return false;
    }
    return socket->IsValid();
}

}
