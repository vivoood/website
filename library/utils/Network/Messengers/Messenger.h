#ifndef __EGT_MESSENGER_H__
#define __EGT_MESSENGER_H__


#include <list>
#include <memory>
#include <map>
#include <mutex>
#include <condition_variable>
//
#include <../UniStream/UniStream.h>
//
#include "../NetworkBase/IConnector.h"
#include "../NetworkBase/IConnection.h"
#include "NetworkPromise.h"
#include "NetworkFuture.h"

namespace egt
{

template<typename MsgType>
class Messenger
{
private:
    constexpr static const uint8_t s_stdMsgChannel = 0;

public:
    using Future = NetworkFuture<MsgType>;
    using FuturePtr = typename NetworkFuture<MsgType>::Ptr;
    using FutureWeakPtr = typename NetworkFuture<MsgType>::WeakPtr;

    struct ConnectionContext
    {
        using FutureWeakPtr = typename Messenger<MsgType>::FutureWeakPtr;
        std::map<uint64_t, FutureWeakPtr> futures;
        uint64_t freeFutureId = 1;
        IConnection::Ptr connection;
    };

public:
    using Duration = std::chrono::milliseconds;
    //
    void Init();
    Messenger();
    ~Messenger();
    void SetConnector(  IConnector::Ptr connector,
                        std::function<void(int connectionId)> onConnect,
                        std::function<void(int connectionId)> onDisconnect,
                        std::function<void(int connectionId, MsgType& msg)> msgRcver,
                        std::function<void(int connectionId, NetworkPromise<MsgType> request)> requetRcver = nullptr);

    bool Process();
    void ProcessBlocking(Duration timeout = Duration(-1));
    void WakeUpProcess();
    void SendMsg(int connectionId, MsgType&& msg);
    FuturePtr SendRequest(int connectionId, MsgType&& msg);
    bool IsConnected(int connectionId);
    void Disconnect(int connectionId);
    void Destroy();

private:
    bool _processInternal(std::unique_lock<std::recursive_mutex>* locker);
    void _attachRemover(int id);
    void _processMsg(int connectionId, MsgType& msg, uint64_t futureId);
    void _disconnect(ConnectionContext& context);

    static void _serialize(MsgType&& from, NetMsg& to);
    static void _deserialize(NetMsg&& from, MsgType& to);

    void _cleanDeadFutures();
    static std::chrono::system_clock::time_point _getWaitTimepoint(Duration timeout);

    using Callback = std::function<void()>;
    using PostProcess = std::function<Callback()>;
    std::vector<PostProcess> m_postprocess;
    std::mutex m_postprocessLocker;
    //
    int m_lastConnectionId = 0;
    IConnector::Ptr m_connector = nullptr;
    std::function<void(int connectionId)> m_onConnect = nullptr;
    std::function<void(int connectionId)> m_onDisconnect = nullptr;
    std::function<void(int connectionId, MsgType& msg)> m_msgRcver = nullptr;
    std::function<void(int connectionId, NetworkPromise<MsgType> request)> m_requestRcver = nullptr;
    std::map<int, ConnectionContext> m_connections;

    std::recursive_mutex m_waitLocker;
    std::condition_variable_any m_eventNotify;
};

}

#include "Messenger.hpp"
#endif // __EGT_MESSENGER_H__
