#ifndef EGT_GENERIC_CLIENT_H
#define EGT_GENERIC_CLIENT_H

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
class GenericClient : public IConnector
{
public:
    using Connection = GenericConnection<SocketImpl>;
    GenericClient();
    ~GenericClient();
    //
    void SetServerInfo(const typename SocketImpl::ServerAddress& address);
    void RunConnector();
protected:
    IConnection::Ptr _waitForConnection(Timepoint waitUntil) final;
    void _stop() final;
private:
    void _connectorLoop();
    bool _reopenSocket();
    bool _connectToHost();
    void _resetConnectionPointer();
    IConnection::Ptr _returnActiveConnection();
    void _sleep();
    void _clearConnectionPointer();
    //
    std::shared_ptr<SocketImpl> m_socket = nullptr;
    //
    typename SocketImpl::ServerAddress m_serverAddress;
    std::atomic<bool> m_isRunning;
    std::thread m_connectorThread;
    std::mutex m_resetConnectionLocker;
    std::mutex m_locker;
    std::mutex m_clearPtrLocker;
    std::condition_variable m_newConnectionEvent;
    //
    std::atomic<bool> m_isNew;
    std::shared_ptr<Connection> m_connection;
};

}
#endif // EGT_GENERIC_CLIENT_H
