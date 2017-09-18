#ifndef EGT_GENERIC_CONNECTION_H
#define EGT_GENERIC_CONNECTION_H
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "../NetworkBase/IConnection.h"

namespace egt{

template<typename SocketImpl>
class GenericConnection : public IConnection
{
public:
    GenericConnection(const GenericConnection&) = delete;
    GenericConnection(GenericConnection&&) = delete;
    void operator=(const GenericConnection&) = delete;
    //
    GenericConnection();
    virtual ~GenericConnection();
    void Start(std::shared_ptr<SocketImpl> socketImpl);
    //
protected:
    WaitResult _waitForMsg(Timepoint waitUntil) final;
    bool _waitForDisconnect(Timepoint waitUntil) final;
    //
    NetMsg _getMsg() final;
    SendResult _sendMsg(NetMsg&& netMsg) final;
    void _disconnect() final;
private:
    bool _isSocketValid() const;
    void _shutdownConnection();
    void _readerLoop();
    void _writerLoop();
    //
    std::queue<NetMsg> m_incomming;
    std::queue<NetMsg> m_outgoing;
    //
    std::mutex m_lockerIn;
    std::mutex m_lockerOut;
    std::mutex m_lockerDisconnect;
    //
    std::condition_variable m_inEvent;
    std::condition_variable m_outEvent;
    std::condition_variable m_disconnectEvent;
    //
    std::thread m_reader;
    std::thread m_writer;
    //
    std::shared_ptr<SocketImpl> m_socket = nullptr;
};

}
#endif // EGT_GENERIC_CONNECTION_H
