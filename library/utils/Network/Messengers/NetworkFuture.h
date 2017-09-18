#ifndef _EGT_NETWORK_FUTURE_H__
#define _EGT_NETWORK_FUTURE_H__
//
#include <memory>
#include <map>
//
#include "../NetworkBase/IConnection.h"


namespace egt{

template<typename MsgType>
class Messenger;

template<typename MsgType>
struct NetworkFuture final
{
private:
    struct Locker{};
public:
    using Ptr = std::shared_ptr<NetworkFuture<MsgType>>;
    using WeakPtr = std::weak_ptr<NetworkFuture<MsgType>>;
    using WaitResult = IConnection::WaitResult;
    using Duration = IConnection::Duration;
    using WaitHandler = std::function<void(Duration timeout)>;
    //
    NetworkFuture(Locker);
    NetworkFuture(NetworkFuture&&)                    = default;
    NetworkFuture& operator= ( NetworkFuture&& )      = default;
    //
    NetworkFuture(const NetworkFuture&)               = delete;
    NetworkFuture& operator= (const NetworkFuture&)   = delete;
    //
    ~NetworkFuture() = default;
    //
    WaitResult WaitForReply(Duration timeout);
    WaitResult CheckForReply();
    WaitResult BlockForReply();
    MsgType GetMsg();
private:
    void _waitForReply(Duration timeout);
    NetworkFuture() = default;
    WaitHandler m_waitHandler = nullptr;
    //
    uint64_t m_id = 0;
    //
    bool m_isReady = false;
    WaitResult m_waitResult = WaitResult::NoMsg;
    MsgType m_msg;
    //
    friend class Messenger<MsgType>;
};

}

#include "NetworkFuture.hpp"
#endif // _EGT_NETWORK_FUTURE_H__
