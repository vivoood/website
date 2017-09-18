#ifndef _EGT_NETWORK_PROMISE_H__
#define _EGT_NETWORK_PROMISE_H__
//
#include <memory>
#include <map>
//
#include "../NetworkBase/IConnection.h"


namespace egt{

template<typename MsgType>
class Messenger;

template<typename MsgType>
struct NetworkPromise final
{
private:
    struct Locker{};
public:
    using Ptr = std::shared_ptr<NetworkPromise<MsgType>>;
    using WeakPtr = std::weak_ptr<NetworkPromise<MsgType>>;
    using WaitResult = IConnection::WaitResult;
    using SendResult = IConnection::SendResult;
    using Duration = IConnection::Duration;
    using ReplyHandler = std::function<IConnection::SendResult(IConnection::Ptr connection, MsgType&& msg)>;
    //
    NetworkPromise(Locker) :NetworkPromise() {}
    NetworkPromise(NetworkPromise&&)                  = default;
    NetworkPromise& operator= ( NetworkPromise&& )    = default;
    //
    NetworkPromise(const NetworkPromise&)             = delete;
    NetworkPromise& operator= (const NetworkPromise&) = delete;
    //
    ~NetworkPromise() = default;
    //
    MsgType& GetRequest();

    SendResult Reply(MsgType& msg);
private:
    NetworkPromise() = default;
    bool m_replyReady = false;
    ReplyHandler m_replyHandler;
    uint64_t m_id = 0;
    MsgType m_msg;
    IConnection::WeakPtr m_connection;
    friend class Messenger<MsgType>;
};
}

#include "NetworkPromise.hpp"
#endif // _EGT_NETWORK_PROMISE_H__
