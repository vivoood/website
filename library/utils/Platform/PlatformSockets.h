#ifndef _EGT_PLATFORM_SOCKETS_H
#define _EGT_PLATFORM_SOCKETS_H
#include <string>
#include <utility>
#include <array>
#include <functional>
#include <mutex>
#include <atomic>

struct sockaddr_in6;
namespace std
{
    class thread;
}

namespace Platform
{
namespace Sockets
{

class Local
{
public:
    using ServerAddress = std::string;
    using ServerConfig = std::string;
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
    //
    bool CreateServer(ServerConfig cfg, int maxConnections = 256);
    //
    bool Listen(Local& newConnection);
    //
    void ShutdownSocket();
    void CloseSocket();
    //
    bool Write(const uint8_t *buff, size_t count);
    bool Read(uint8_t *buff, size_t count);
    bool Peek(uint8_t *buff, size_t count);

private:
    int _getId() const;
    void _setId(int id);
    mutable std::mutex m_idLocker;
    int m_id_ = -1;
    std::atomic<bool> m_isShutdown {false};
    ServerAddress m_address;
};

class IpV6
{
public:
    using ServerAddress = std::pair<std::string, int>;
    using ServerConfig = int;
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
    //
    bool CreateServer(ServerConfig cfg, int maxConnections = 256);
    //
    bool Listen(IpV6& newConnection);
    //
    void ShutdownSocket();
    void CloseSocket();
    //
    bool Write(const uint8_t *buff, size_t count);
    bool Read(uint8_t *buff, size_t count);
    bool Peek(uint8_t *buff, size_t count);

private:
    bool _resolveServerAddress();
    void _releaseServerAddress();

    //sockaddr_in6 m_clientInfo;
    int _getId() const;
    void _setId(int id);
    mutable std::mutex m_idLocker;
    int m_id_ = -1;
    ServerAddress m_serverAddress;
    std::atomic<bool> m_isShutdown {false};
    struct addrinfo* m_resolvedAddress = nullptr;
};


class UdpV6Reader
{
public:
    using ServerAddress = std::pair<std::string, int>;
    using ServerConfig = int;
    //
    bool IsValid() const;
    static bool CanRead();
    static bool CanWrite();
    //
    bool CreateClient(const ServerAddress& address);
    //
    bool ConnectToServer();
    //
    void ShutdownSocket();
    void CloseSocket();
    //
    bool Write(const uint8_t *buff, size_t count);
    bool Read(uint8_t *buff, size_t count);
    bool Peek(uint8_t *buff, size_t count);

private:
    bool _resolveServerAddress();
    void _releaseServerAddress();

    //sockaddr_in6 m_clientInfo;
    int _getId() const;
    void _setId(int id);
    mutable std::mutex m_idLocker;
    int m_id_ = -1;
    ServerAddress m_serverAddress;
    std::atomic<bool> m_isShutdown {false};
    struct addrinfo* m_resolvedAddress = nullptr;
};

class UdpV6Writer
{
public:
    using ServerAddress = std::pair<std::string, int>;
    using ServerConfig = int;
    //
    bool IsValid() const;
    static bool CanRead();
    static bool CanWrite();
    //
    bool CreateClient(const ServerAddress& address);
    //
    bool ConnectToServer();
    //
    void ShutdownSocket();
    void CloseSocket();
    //
    bool Write(const uint8_t *buff, size_t count);
    bool Read(uint8_t *buff, size_t count);
    bool Peek(uint8_t *buff, size_t count);

private:
    bool _resolveServerAddress();
    void _releaseServerAddress();

    //sockaddr_in6 m_clientInfo;
    int _getId() const;
    void _setId(int id);
    mutable std::mutex m_idLocker;
    int m_id_ = -1;
    ServerAddress m_serverAddress;
    std::atomic<bool> m_isShutdown {false};
    struct addrinfo* m_resolvedAddress = nullptr;
};

class ExecProcess
{
public:
    using ServerAddress = std::string;
    using ServerConfig = int;

    ExecProcess();

    // Disable copy and move
    explicit ExecProcess(const ExecProcess &) = delete;
    explicit ExecProcess(ExecProcess &&) = delete;

    ~ExecProcess();

    // Disable copy and move
    ExecProcess &operator=(const ExecProcess &) = delete;
    ExecProcess &operator=(ExecProcess &&) = delete;

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
    //
    bool CreateServer(ServerConfig cfg, int maxConnections = 256);
    //
    bool Listen(ExecProcess& newConnection);
    //
    void ShutdownSocket();
    void CloseSocket();
    //
    bool Write(const uint8_t *buff, size_t count);
    bool Read(uint8_t *buff, size_t count);
    bool Peek(uint8_t *buff, size_t count);

private:
    static void _globalSignalHandler(int signal);
    static std::function<void(int)> mGlobalSignalHadleAction;

    void _signalHandler(int signal);
    void _killProcess();
    bool _startProcess();
    std::array<int, 2> m_childInId;
    std::array<int, 2> m_childOutId;
    pid_t m_childId = 0;
    bool m_isValid = false;
    //
    ServerAddress m_processName;
};

}
}

#endif // _EGT_PLATFORM_SOCKETS_H
