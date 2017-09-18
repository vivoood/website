#ifndef EGT_BASH_CLIENT_H
#define EGT_BASH_CLIENT_H
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <lib_utils/Platform/PlatformSockets.h>
#include "../NetworkBase/IConnection.h"


namespace egt{

namespace bash_client
{
class StringLineProxy
{
public:
    using SockImpl = Platform::Sockets::ExecProcess;
    using ServerAddress = SockImpl::ServerAddress;
    using ServerConfig = SockImpl::ServerConfig;
    //
    bool IsValid() const;
    static bool CanRead();
    static bool CanWrite();
    //
    bool CreateClient(const ServerAddress& address);
    //
    bool ConnectToServer();
    //
    //
    bool CreateServer(ServerConfig cfg, int maxConnections = 256);
    //
    bool Listen(StringLineProxy& newConnection);
    //
    void ShutdownSocket();
    void CloseSocket();
    //
    bool Write(const uint8_t *buff, size_t count);
    bool Read(uint8_t *buff, size_t count);
    bool Peek(uint8_t *buff, size_t count);

private:
    ServerAddress m_address;
    SockImpl m_sockImpl;

    std::mutex m_dataLocker;
    std::queue<std::string> m_readyData;
};

}}
#endif // EGT_BASH_CLIENT_H
