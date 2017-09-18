#ifndef LocalSERVER_H
#define LocalSERVER_H

#include <memory>
#include <mutex>
#include <atomic>
#include <condition_variable>
//
#include <netinet/in.h>
//
#include "../NetworkBase/IConnector.h"

namespace egt{

class LocalConnection;
class LocalClient;

class LocalServer : public IConnector
{
public:
    LocalServer();
    virtual ~LocalServer();
    //
    void RunConnector();
protected:
    IConnection::Ptr _waitForConnection(Timepoint waitUntil) final;
    void _stop() final;
private:
    IConnection::Ptr _returnActiveConnection();

    std::atomic<bool> m_isRunning{false};
    std::mutex m_newClientLocker;
    std::condition_variable m_newClientEvent;
    std::vector<std::shared_ptr<LocalConnection>> m_connections;
    friend class egt::LocalClient;
};

}
#endif // LocalSERVER_H
