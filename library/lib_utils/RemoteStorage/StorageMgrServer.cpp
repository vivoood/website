#include <lib_utils/Platform/Platform.h>
//
#include "StorageMgrServer.h"

namespace egt
{
namespace RemoteStorage
{

enum class StorageMgrMsgId
{
    MsgIdSendRequest
};

Server::Server()
{
}


Server::~Server()
{
    Stop();
}

void Server::Stop()
{
    m_isAlive = false;
    m_net.WakeUpProcess();
    if (m_process.joinable()) m_process.join();
}

void Server::Init(IConnector::Ptr connector, WriterHandler writer, ReaderHandler reader)
{
    m_writer = writer;
    m_reader = reader;
    m_isAlive = true;
    m_net.SetConnector(connector,
        nullptr, // on connect
        [this](int connectionId) // on disconnect
        {
            _cleanupConnection(connectionId);
        },
        [this](int connectionId, UniMsg& msg) // on new msg received
        {
            _onMsgReceived(connectionId, msg);
        },
        [this](int, NetworkPromise<UniMsg> requestPromise) // on request received
        {
            _requestHandler(std::move(requestPromise));
        });
    // TODO: check
    m_process = std::thread([this]()
    {
        while(m_isAlive)
        {
            m_net.ProcessBlocking();
        }
    });
    auto threadName = "p_" + connector->GetName();
    Platform::Threads::ChangeName(m_process, threadName);
}

void Server::WriteDataCallback(uint32_t transactionId, WriteRequest request)
{
    int gameId = request.gameId;
    if (request.isGameParam == false)
    {
        gameId = -1;
    }

    std::lock_guard<std::mutex> locker(m_paramsLocker);

    for (auto& p : m_paramsPerConnection)
    {
        auto connectionId = p.first;
        const auto& paramsMap = p.second;
        auto it = paramsMap.find(gameId);
        if (it == paramsMap.end())
        {
            continue;
        }
        auto& paramsSet = it->second;
        if (paramsSet.find(request.dataKey) == paramsSet.end())
        {
            continue;
        }
        m_pendingChanges[transactionId][connectionId].push_back(request);
    }
}

void Server::FlushTransactionCallback(uint32_t transactionId)
{
    std::lock_guard<std::mutex> locker(m_paramsLocker);
    auto it = m_pendingChanges.find(transactionId);
    if (it == m_pendingChanges.end())
    {
        return;
    }
    auto& connectionsMap = it->second;
    for (auto& p : connectionsMap)
    {
        ConnectionId connection = p.first;
        auto& requests = p.second;
        UniMsg msg;
        msg.name = "on_change";
        msg.AddValue("changes", requests);
        m_net.SendMsg(connection, std::move(msg));
    }

    m_pendingChanges.erase(it);
}

void Server::CancelTransactionCallback(uint32_t transactionId)
{
    std::lock_guard<std::mutex> locker(m_paramsLocker);
    auto it = m_pendingChanges.find(transactionId);
    if (it == m_pendingChanges.end())
    {
        return;
    }
    m_pendingChanges.erase(it);
}

void Server::_requestHandler(NetworkPromise<UniMsg> requestPromise)
{
    UniMsg &msg = requestPromise.GetRequest();

    if (msg.name == "write_data")
    {
        _write(std::move(requestPromise));
    }
    else if (msg.name == "read_data")
    {
        _read(std::move(requestPromise));
    }
    else
    {
        UniMsg replyMsg;
        replyMsg.name = msg.name;
        replyMsg.AddValue("bool_result", false);
        requestPromise.Reply(replyMsg);
    }
}

void Server::_onMsgReceived(int connectionId, UniMsg &msg)
{
    if (msg.name == "register_param")
    {
        int gameId = msg.gameId;
        bool isGameParam = false;
        std::string paramKey;
        if (false == msg.GetValue("is_game_param", isGameParam))
        {
            return;
        }
        if (false == msg.GetValue("param_key", paramKey))
        {
            return;
        }
        if (isGameParam)
        {
            _registerGameParam(connectionId, paramKey, gameId);
        }
        else
        {
            _registerParam(connectionId, paramKey);
        }
    }
}

void Server::_registerParam(int connectionId, const std::string &paramId)
{
    std::lock_guard<std::mutex> locker(m_paramsLocker);
    int hatId = -1;
    m_paramsPerConnection[connectionId][hatId].insert(paramId);
}

void Server::_registerGameParam(int connectionId, const std::string &paramId, int gameId)
{
    std::lock_guard<std::mutex> locker(m_paramsLocker);
    m_paramsPerConnection[connectionId][gameId].insert(paramId);
}

void Server::_cleanupConnection(int connectionId)
{
    std::lock_guard<std::mutex> locker(m_paramsLocker);
    {
        auto connIt = m_paramsPerConnection.find(connectionId);
        if (connIt != m_paramsPerConnection.end())
        {
            m_paramsPerConnection.erase(connIt);
        }
    }
    {
        for (auto& p : m_pendingChanges)
        {
            auto& connections = p.second;
            auto connIt = connections.find(connectionId);
            if (connIt != connections.end())
            {
                connections.erase(connIt);
            }
        }
    }
}

void Server::_write(NetworkPromise<UniMsg> promise)
{
    UniMsg& msg = promise.GetRequest();
    UniMsg replyMsg;
    auto reply = [&promise, &replyMsg](bool ok)
    {
        replyMsg.AddValue("bool_result", ok);
        promise.Reply(replyMsg);
    };

    bool ok = true;
    ok = ok && msg.HasValue("requests");
    ok = ok && (m_writer != nullptr);

    if (ok == false)
    {
        reply(false);
        return;
    }
    std::vector<WriteRequest> requests;
    msg.GetValue("requests", requests);
    auto writeResult = m_writer(requests);
    reply(writeResult);
}

void Server::_read(NetworkPromise<UniMsg> promise)
{
    UniMsg& msg = promise.GetRequest();
    UniMsg replyMsg;
    auto reply = [&promise, &replyMsg](bool ok)
    {
        replyMsg.AddValue("bool_result", ok);
        promise.Reply(replyMsg);
    };

    bool ok = true;
    ok = ok && msg.HasValue("requests");
    ok = ok && (m_reader != nullptr);

    if (ok == false)
    {
        reply(false);
        return;
    }
    std::vector<ReadRequest> requests;
    msg.GetValue("requests", requests);
    auto readResults = m_reader(requests);
    replyMsg.AddValue("results", readResults);
    reply(true);
}

}}

