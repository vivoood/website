#include "StorageMgrClient.h"
#include "StorageMirror.h"

namespace egt
{
namespace RemoteStorage
{

Client::Client(Locker)
{
}


Client::Ptr Client::CreateInstance()
{
    auto ptr = std::make_shared<Client>(Locker());
    ptr->m_ownPtr = ptr;
    return ptr;
}

Client::~Client()
{
    Stop();
}

void Client::Stop()
{
    //m_net.Stop();
}

void Client::Init(IConnector::Ptr connector)
{
    m_net.SetConnector(connector,
        [this](int connectionId)
        {
            _onConnect(connectionId);
        }, // on connect
        [this](int connectionId)
        {
            _onDisconnect(connectionId);
        }, // on disconnect
        [this](int connectionId, UniMsg& msg){_msgHandler(connectionId, msg);}, // on msg rcved
        nullptr);
}

void Client::Process()
{
    m_net.Process();
}

void Client::_msgHandler(int connectionId, UniMsg& msg)
{
    if (connectionId != m_serverConnectionId)
    {
        // Assert
        return;
    }
    if (msg.name == "on_change")
    {
        std::vector<WriteRequest> changes;
        if (true == msg.GetValue("changes", changes))
        {
            _onChange(changes);
        }
    }
}

bool Client::Write(std::vector<WriteRequest> &requests)
{
    std::lock_guard<std::recursive_mutex> lock(m_netLocker);
    if (m_serverConnectionId <= 0)
    {
        return false;
    }
    UniMsg requestMsg;
    requestMsg.name = "write_data";
    requestMsg.AddValue("requests", requests);
    auto requestFuture = m_net.SendRequest(m_serverConnectionId, std::move(requestMsg));
    auto waitResult = requestFuture->BlockForReply();
    if (waitResult != WaitResult::NewMsg)
    {
        // TODO: call assert handler
        return false;
    }
    auto reply = requestFuture->GetMsg();
    return _processWriteResult(reply);
}

std::vector<ReadResult> Client::Read(std::vector<ReadRequest> &requests)
{
    std::lock_guard<std::recursive_mutex> lock(m_netLocker);
    if (m_serverConnectionId <= 0)
    {
        return {};
    }
    UniMsg requestMsg;
    requestMsg.name = "read_data";
    requestMsg.AddValue("requests", requests);
    auto requestFuture = m_net.SendRequest(m_serverConnectionId, std::move(requestMsg));
    auto waitResult = requestFuture->BlockForReply();
    if (waitResult != WaitResult::NewMsg)
    {
        // TODO: call assert handler
        return {};
    }
    auto reply = requestFuture->GetMsg();
    bool isOk = false;
    reply.GetValue("bool_result", isOk);
    if (isOk == false)
    {
        return {};
    }
    std::vector<ReadResult> results;
    reply.GetValue("results", results);
    return results;
}

bool Client::WaitForConnection(Client::Duration timeout)
{
    std::lock_guard<std::recursive_mutex> lock(m_netLocker);
    if (m_serverConnectionId > 0)
    {
        return true;
    }
    m_net.ProcessBlocking(timeout);
    return m_serverConnectionId > 0;
}

Client::StorageMirrorPtr Client::CreateStorageMirror()
{
    auto mirror = StorageMirror::CreateInstance(StorageMirror::Locker(), m_ownPtr);
    return mirror;
}

void Client::RegisterParam(const std::string &paramKey, Client::StorageMirrorWeakPtr mirrorWeak)
{
    RegisterGameParam(paramKey, -1, mirrorWeak);
}

void Client::RegisterGameParam(const std::string &paramKey, int gameId, Client::StorageMirrorWeakPtr mirrorWeak)
{
    if (m_serverConnectionId <= 0)
    {
        return;
    }
    m_mirrorsPerParam[gameId][paramKey].push_back(mirrorWeak);
    bool isGameParam = (gameId > -1);
    //
    UniMsg msg;
    msg.name = "register_param";
    msg.gameId = gameId;
    msg.AddValue("is_game_param", isGameParam);
    msg.AddValue("param_key", paramKey);
    m_registrationMessages.push_back(msg);
    if (m_serverConnectionId > 0)
    {
        m_net.SendMsg(m_serverConnectionId, std::move(msg));
    }
}

bool Client::_processWriteResult(UniMsg &msg)
{
    bool ret = false;
    msg.GetValue("bool_result", ret);

    return ret;
}

void Client::_onConnect(int connectionId)
{
    m_serverConnectionId = connectionId;
    for (auto msgCopy : m_registrationMessages)
    {
        m_net.SendMsg(connectionId, std::move(msgCopy));
    }
}

void Client::_onDisconnect(int connectionId)
{
    if (m_serverConnectionId == connectionId)
    {
        m_serverConnectionId = -1;
        // TODO: call assert handler
    }
}

void Client::_onChange(const std::vector<WriteRequest> &changes)
{
    bool dirty = false;

    std::map<StorageMirrorPtr, std::vector<WriteRequest>> requests;
    for (const auto& change : changes)
    {
        int gameId = -1;
        if (change.isGameParam == true)
        {
            gameId = change.gameId;
        }
        const auto gameIt = m_mirrorsPerParam.find(gameId);
        if (gameIt == m_mirrorsPerParam.end())
        {
            continue;
        }
        const auto& mirrorsPerGame = gameIt->second;
        const auto mirrorsIt = mirrorsPerGame.find(change.dataKey);
        if (mirrorsIt == mirrorsPerGame.end())
        {
            continue;
        }
        const auto& mirrors = mirrorsIt->second;
        for (const auto& mirrorWeak : mirrors)
        {
            auto mirror = mirrorWeak.lock();
            if (mirror == nullptr)
            {
                dirty = true;
                continue;
            }
            requests[mirror].push_back(change);
        }
    }
    for (const auto& p : requests)
    {
        auto mirror = p.first;
        const auto& changes = p.second;

        mirror->OnChange(changes);
    }

    if (dirty)
    {
        _cleanupMirrors();
    }
}

void Client::_cleanupMirrors()
{
    decltype (m_mirrorsPerParam) newMirrors;

    for (const auto& gamePair : m_mirrorsPerParam)
    {
        const auto& gameId = gamePair.first;
        const auto& mirrors = gamePair.second;
        for (const auto& paramPair : mirrors)
        {
            const auto& paramId = paramPair.first;
            const auto& mirrorsContainer = paramPair.second;
            for (const auto& mirrorWeak : mirrorsContainer)
            {
                if (mirrorWeak.expired() == true)
                {
                    continue;
                }
                newMirrors[gameId][paramId].push_back(mirrorWeak);
            }
        }
    }
    m_mirrorsPerParam.clear();
    m_mirrorsPerParam = std::move(newMirrors);
}

}}

