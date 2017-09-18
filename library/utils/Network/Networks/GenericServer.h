#ifndef EGT_GENERIC_SERVER_H
#define EGT_GENERIC_SERVER_H

#include <memory>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
//
#include "../NetworkBase/IConnector.h"

namespace egt{

template<typename SocketImpl>
class GenericConnection;

template<typename SocketImpl>
class GenericServer : public IConnector
{
public:
    using Connection = GenericConnection<SocketImpl>;
    GenericServer();
    virtual ~GenericServer();
    //
    void SetServerInfo(typename SocketImpl::ServerConfig serverCfg);
    void RunConnector();
protected:
    IConnection::Ptr _waitForConnection(Timepoint waitUntil) final;
    void _stop() final;
private:
    void _serverLoop();
    void _acceptConnections();
    IConnection::Ptr _returnActiveConnection();
    void _createServer();
    void _sleep();
    void _shutdownServerSocket();

    std::thread m_connectorThread;
    std::atomic<bool> m_isRunning;
    std::mutex m_locker;
    std::condition_variable m_newConnectionEvent;
    std::shared_ptr<SocketImpl> m_socket = nullptr;
    typename SocketImpl::ServerConfig m_cfg;

    std::shared_ptr<Connection> m_connection;
};

}
#endif // EGT_GENERIC_SERVER_H
