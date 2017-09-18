#ifndef LocalCLIENT_H
#define LocalCLIENT_H

#include <memory>
#include <atomic>
//
#include "../NetworkBase/IConnector.h"
#include "LocalServer.h"

namespace egt{
class LocalConnection;
class LocalClient : public IConnector
{
public:
    LocalClient();
    ~LocalClient();
    //
    void SetServer(std::weak_ptr<LocalServer> server);
    void RunConnector();
protected:
    IConnection::Ptr _waitForConnection(Timepoint waitUntil) final;
    void _stop() final;
    IConnection::Ptr _createConnection();
private:
    //
    std::atomic<bool> m_isRunning{false};
    std::weak_ptr<LocalServer> m_server;
    std::shared_ptr<LocalConnection> m_connection;
};

}
#endif // LocalCLIENT_H
