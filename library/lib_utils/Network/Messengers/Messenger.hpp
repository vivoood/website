namespace egt
{

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void Messenger<MsgType>::Init()
{

}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
Messenger<MsgType>::Messenger()
{

}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
Messenger<MsgType>::~Messenger()
{
    Destroy();
}

template<typename MsgType>
void Messenger<MsgType>::Disconnect(int connectionId)
{
    auto it = m_connections.find(connectionId);
    if (it == m_connections.end())
    {
        return;
    }
    auto& context = it->second;
    _disconnect(context);
    m_connections.erase(it);
}

template<typename MsgType>
void Messenger<MsgType>::Destroy()
{
    if (m_connector != nullptr)
    {
        m_connector->SetEventCallback(nullptr);
        m_connector->Stop();
    }

    for (auto& contextPair : m_connections)
    {
        auto& context = contextPair.second;
        _disconnect(context);
    }
    m_connections.clear();
}


template<typename MsgType>
void Messenger<MsgType>::_disconnect(ConnectionContext& context)
{
    context.connection->SetEventCallback(nullptr);
    for(auto& futurePair : context.futures)
    {
        auto& futureWeak = futurePair.second;
        auto futurePtr = futureWeak.lock();
        if (futurePtr != nullptr)
        {
            futurePtr->m_isReady = true;
            futurePtr->m_waitResult = IConnection::WaitResult::Disconnected;
        }
    }
    context.connection->Disconnect();
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void Messenger<MsgType>::SetConnector(
                            IConnector::Ptr connector,
                            std::function<void(int connectionId)> onConnect,
                            std::function<void(int connectionId)> onDisconnect,
                            std::function<void(int connectionId, MsgType& msg)> msgRcver,
                            std::function<void(int connectionId, NetworkPromise<MsgType> request)> requestRcver)
{
    m_connector = connector;
    m_onConnect = onConnect;
    m_onDisconnect = onDisconnect;
    m_msgRcver = msgRcver;
    m_requestRcver = requestRcver;
    m_connector->SetEventCallback([this]()
    {
        WakeUpProcess();
    });
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
bool Messenger<MsgType>::Process()
{
    bool result = _processInternal(nullptr);
    return result;
}

template<typename MsgType>
bool Messenger<MsgType>::_processInternal(std::unique_lock<std::recursive_mutex>* locker)
{
    bool result = false;
    _cleanDeadFutures();
    if (m_connector != nullptr)
    {
        auto newConnection = m_connector->CheckForConnection();
        if (newConnection != nullptr)
        {
            result = true;
            m_lastConnectionId++;
            auto& newContext = m_connections[m_lastConnectionId];
            newContext.connection = newConnection;
            newConnection->SetEventCallback([this]()
            {
                WakeUpProcess();
            });
            if (nullptr != m_onConnect)
            {
                if(nullptr != locker)
                {
                    locker->unlock();
                }

                m_onConnect(m_lastConnectionId);

                if(nullptr != locker)
                {
                    locker->lock();
                }
            }
        }
        for (auto p : m_connections)
        {
            int id = p.first;
            auto& context = p.second;
            auto waitResult = context.connection->CheckForMsg();
            switch (waitResult)
            {
            case IConnection::WaitResult::NewMsg:
            {
                result = true;
                MsgType msg;
                NetMsg netMsg = context.connection->GetMsg();
                uint64_t futureId = netMsg.channel;

                _deserialize(std::move(netMsg), msg);

                if(nullptr != locker)
                {
                    locker->unlock();
                }

                _processMsg(id, msg, futureId);

                if(nullptr != locker)
                {
                    locker->lock();
                }
            }break;
            case IConnection::WaitResult::NoMsg:
            {
            }break;
            default:
            {
                result = true;
                _attachRemover(id);
            }break;
            }
        }
    }

    std::vector<Callback> callbacks;
    {
        std::lock_guard<std::mutex> postProcessLock(m_postprocessLocker);
        for(auto& f : m_postprocess)
        {
            if(nullptr != locker)
            {
                locker->unlock();
            }
            auto callback = f();
            if(nullptr != locker)
            {
                locker->lock();
            }
            if (nullptr != callback)
            {
                result = true;
                callbacks.push_back(callback);
            }
        }
        m_postprocess.clear();
    }


    for (auto callback : callbacks)
    {
        if(nullptr != locker)
        {
            locker->unlock();
        }

        callback();

        if(nullptr != locker)
        {
            locker->lock();
        }
    }

    return result;
}

template<typename MsgType>
void Messenger<MsgType>::ProcessBlocking(Duration timeout)
{
    std::unique_lock<std::recursive_mutex> locker(m_waitLocker);
    if (_processInternal(&locker))
    {
        return;
    }
    auto waitUntil = _getWaitTimepoint(timeout);
    m_eventNotify.wait_until(locker, waitUntil);
    _processInternal(&locker);
}

template<typename MsgType>
void Messenger<MsgType>::WakeUpProcess()
{
    std::lock_guard<std::recursive_mutex> locker(m_waitLocker);
    m_eventNotify.notify_all();
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void Messenger<MsgType>::SendMsg(int connectionId, MsgType&& msg)
{
    IConnection::SendResult sendResult = IConnection::SendResult::Error;
    {
        std::lock_guard<std::mutex> locker(m_postprocessLocker);
        //
        auto connIt = m_connections.find(connectionId);
        if (connIt == m_connections.end())
        {
            return;
        }
        auto connection = connIt->second.connection;

        NetMsg netMsg;
        _serialize(std::move(msg), netMsg);
        netMsg.channel = s_stdMsgChannel;

        sendResult = connection->SendMsg(std::move(netMsg));
    }
    if (IConnection::SendResult::SendOk != sendResult)
    {
        _attachRemover(connectionId);
    }
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
typename Messenger<MsgType>::FuturePtr Messenger<MsgType>::SendRequest(int connectionId, MsgType &&msg)
{
    std::lock_guard<std::mutex> locker(m_postprocessLocker);

    IConnection::SendResult sendResult = IConnection::SendResult::Error;
    //
    auto connIt = m_connections.find(connectionId);
    if (connIt == m_connections.end())
    {
        auto brokenFuture = std::make_shared<Future>(typename Future::Locker());
        brokenFuture->m_isReady = true;
        brokenFuture->m_waitResult = IConnection::WaitResult::Error;
        return brokenFuture;
    }
    auto& context = connIt->second;
    auto connection = context.connection;
    uint64_t id = context.freeFutureId++;

    NetMsg netMsg;
    _serialize(std::move(msg), netMsg);
    netMsg.channel = id;

    sendResult = connection->SendMsg(std::move(netMsg));
    if (sendResult == IConnection::SendResult::SendOk)
    {
        auto newFuture = std::make_shared<Future>(typename Future::Locker());
        //
        newFuture->m_id = id | (1ull << 63); // prepare id for compare
        newFuture->m_waitHandler = [this](Duration timeout)
        {
            ProcessBlocking(timeout);
        };

        context.futures[newFuture->m_id] = newFuture;
        return newFuture;
    }
    _attachRemover(connectionId);
    auto brokenFuture = std::make_shared<Future>(typename Future::Locker());
    brokenFuture->m_isReady = true;
    brokenFuture->m_waitResult = IConnection::WaitResult::Disconnected;
    return brokenFuture;
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
bool Messenger<MsgType>::IsConnected(int connectionId)
{
    std::lock_guard <std::mutex> locker(m_postprocessLocker);
    auto connIter = m_connections.find(connectionId);
    if (connIter == m_connections.end())
    {
        return false;
    }

    auto conntection = connIter->second.connection;
    bool res = conntection->WaitForDisconnect( std::chrono::milliseconds(0) );
    return !res;
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void Messenger<MsgType>::_attachRemover(int id)
{
    auto remover = [this, id]() -> Callback
    {
        auto onDisconnect = m_onDisconnect;
        auto it = m_connections.find(id);
        if (it == m_connections.end())
        {
            return nullptr;
        }
        for (auto& futurePair : it->second.futures)
        {
            auto& futureWeak = futurePair.second;
            auto futurePtr = futureWeak.lock();
            if ((futurePtr == nullptr) || (futurePtr->m_isReady == true))
            {
                continue;
            }
            futurePtr->m_isReady = true;
            futurePtr->m_waitResult = IConnection::WaitResult::Disconnected;
        }
        it->second.futures.clear();
        it->second.connection->Disconnect();
        m_connections.erase(id);

        if (onDisconnect != nullptr)
        {
            return [onDisconnect, id](){onDisconnect(id);};
        }
        return nullptr;
    };
    std::lock_guard<std::mutex> locker(m_postprocessLocker);
    m_postprocess.push_back(remover);
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void Messenger<MsgType>::_processMsg(int connectionId, MsgType &msg, uint64_t futureId)
{
    if (futureId == s_stdMsgChannel)
    {
        if (nullptr != m_msgRcver)
        {
            m_msgRcver(connectionId, msg);
        }
    }
    else
    {
        if ((futureId & (1ull << 63)) != 0)
        {
            // this msg is reply
            // find waiting future and apply the reply
            auto& context = m_connections[connectionId];
            auto it = context.futures.find(futureId);
            if (it == context.futures.end())
            {
                return;
            }
            auto& futureWeak = it->second;
            auto activeFuture = futureWeak.lock();
            context.futures.erase(futureId);
            if (nullptr == activeFuture)
            {
                return;
            }
            activeFuture->m_isReady = true;
            activeFuture->m_waitResult = IConnection::WaitResult::NewMsg;
            activeFuture->m_msg = std::move(msg);
        }
        else
        {
            // we received new request
            // create new promise and send it to the user callback
            if (m_requestRcver != nullptr)
            {
                NetworkPromise<MsgType> newPromise{typename NetworkPromise<MsgType>::Locker()};
                newPromise.m_id = futureId;
                newPromise.m_msg = std::move(msg);
                newPromise.m_connection = m_connections[connectionId].connection;
                newPromise.m_replyHandler = [futureId](IConnection::Ptr connection, MsgType&& msg)
                {
                    auto replyId = futureId | (1ull << 63);
                    NetMsg netMsg;
                    _serialize(std::move(msg), netMsg);
                    netMsg.channel = replyId;

                    return connection->SendMsg(std::move(netMsg));
                };

                m_requestRcver(connectionId, std::move(newPromise));
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void Messenger<MsgType>::_serialize(MsgType&& from, NetMsg& to)
{
    egt::oUniStream out;
    out << from;
    to = {0, 0, std::move(out.GetBuffer())};
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void Messenger<MsgType>::_deserialize(NetMsg&& from, MsgType& to)
{
    egt::iUniStream input(from.payload);
    input >> to;
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void Messenger<MsgType>::_cleanDeadFutures()
{
    for (auto& contextPair : m_connections)
    {
        auto& context = contextPair.second;
        std::vector<uint64_t> deadFutures;
        for (auto& futurePair : context.futures)
        {
            if (futurePair.second.lock() == nullptr)
            {
                deadFutures.push_back(futurePair.first);
            }
        }
        for (auto futureId : deadFutures)
        {
            context.futures.erase(futureId);
        }
    }
}

///////////////////////////////////////////////////////////////////////
template<>
inline void Messenger<NetMsg>::_serialize(NetMsg&& from, NetMsg& to)
{
    to = std::move(from);
}

///////////////////////////////////////////////////////////////////////
template<>
inline void Messenger<NetMsg>::_deserialize(NetMsg&& from, NetMsg& to)
{
    to = std::move(from);
}

///////////////////////////////////////////////////////////////////////
template<>
inline void Messenger<std::string>::_serialize(std::string&& from, NetMsg& to)
{
    to.payload.clear();
    to.payload.reserve(from.size());
    for (auto c : from)
    {
        to.payload.push_back(c);
    }
    to.channel = 0;
}

///////////////////////////////////////////////////////////////////////
template<>
inline void Messenger<std::string>::_deserialize(NetMsg&& from, std::string& to)
{
    to.clear();
    for (auto c : from.payload)
    {
        to.push_back(c);
    }
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
std::chrono::system_clock::time_point Messenger<MsgType>::_getWaitTimepoint(Duration timeout)
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

