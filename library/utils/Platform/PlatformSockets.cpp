#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/un.h>
#include <signal.h>
//
#include "PlatformSockets.h"
// #include <egt_lib/debug/egt_debug.h>


namespace Platform
{
namespace Sockets
{


///////////////////////////////////////////////////////////////////////////
bool _write(int id, const uint8_t *buff, size_t count)
{
    // writer thread
    while(count)
    {
        auto writeCnt = write(id, buff, count);
        if (writeCnt <= 0)
        {
            return false;
        }
        buff += writeCnt;
        if (writeCnt > (int64_t)count)
        {
            return false;
        }
        count -= (size_t)writeCnt;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool _writeUdp(int id, addrinfo* addr, const uint8_t* data, size_t count)
{
    size_t left = count;
    while(left)
    {
        auto writeCnt = sendto(id, data + count - left, left, 0, addr->ai_addr, addr->ai_addrlen);
        if (writeCnt <= 0)
        {
            return false;
        }
        left -= (size_t)writeCnt;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool _read(int id, uint8_t *buff, size_t count)
{
    // reader thread
    while(count)
    {
        int readCnt = read(id, buff, count);
        if (readCnt <= 0)
        {
            return false;
        }
        buff += readCnt;
        count -= readCnt;
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////
bool _readUdp(int id, uint8_t *buff, size_t count)
{
    size_t left = count;
    while (left)
    {
         auto bytesRead = recvfrom(id, buff + count - left, left, 0, NULL, 0);
         if (bytesRead <= 0)
         {
             return false;
         }
        left -= (size_t)bytesRead;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool _peek(int id, uint8_t *buff, size_t count)
{
    size_t buffSize = count;
    while (count)
    {
         auto bytesRead = recvfrom(id, buff + buffSize - count, count, MSG_PEEK, NULL, 0);
         if (bytesRead <= 0)
         {
             return false;
         }
        count -= (size_t)bytesRead;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
void _close(int id)
{
    if (id < 0)
    {
        return;
    }
    close(id);
}

void _shutdow(int id)
{
    if (id < 0)
    {
        return;
    }
    shutdown(id, SHUT_RDWR);
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
bool Local::IsValid() const
{
    int id = _getId();
    if (m_isShutdown == true)
    {
        return false;
    }
    return id > 0;
}

///////////////////////////////////////////////////////////////////////////
bool Local::CanRead()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool Local::CanWrite()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool Local::CreateClient(const ServerAddress& address)
{
    int id = socket(AF_UNIX, SOCK_STREAM, 0);

    if (id <= 0)
    {
        return false;
    }
    _setId(id);
    m_isShutdown = false;
    m_address = address;
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool Local::ConnectToServer()
{
    if (IsValid() == false)
    {
        return false;
    }
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    if(m_address.empty() == true)
    {
        *addr.sun_path = '\0';
        strncpy(addr.sun_path+1, m_address.c_str() + 1, sizeof(addr.sun_path)-2);
    }
    else
    {
        strncpy(addr.sun_path, m_address.c_str(), sizeof(addr.sun_path)-1);
    }
    int id = _getId();
    auto err = connect(id, (struct sockaddr*)&addr, sizeof(addr));
    if (err < 0)
    {
        ShutdownSocket();
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool Local::CreateServer(ServerConfig cfg, int maxConnections)
{
    auto& socketName = cfg;

    int id = socket(AF_UNIX, SOCK_STREAM, 0);
    if (id <= 0)
    {
        _setId(-1);
        return false;
    }
    _setId(id);
    m_isShutdown = false;
    sockaddr_un servAddr;
    servAddr.sun_family = AF_UNIX;

    if(socketName.empty() == true)
    {
        *servAddr.sun_path = '\0';
        strncpy(servAddr.sun_path+1, socketName.c_str() + 1, sizeof(servAddr.sun_path)-2);
    }
    else
    {
        strncpy(servAddr.sun_path, socketName.c_str(), sizeof(servAddr.sun_path)-1);
        unlink(socketName.c_str());
    }

    int bindResult = bind(id, (struct sockaddr *) &servAddr, sizeof(servAddr));
    if (bindResult < 0)
    {
        ShutdownSocket();
        CloseSocket();
        return false;
    }
    if (listen(id, maxConnections))
    {
        ShutdownSocket();
        CloseSocket();
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool Local::Listen(Local& newConnection)
{
    int id = _getId();
    int result = accept(id, nullptr, nullptr);
    if (result <= 0)
    {
        ShutdownSocket();
        newConnection._setId(-1);
        return false;
    }
    newConnection._setId(result);
    return true;
}

///////////////////////////////////////////////////////////////////////////
void Local::CloseSocket()
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    _close(m_id_);
    m_id_ = -1;
}

///////////////////////////////////////////////////////////////////////////
void Local::ShutdownSocket()
{
    if (IsValid() == false)
    {
        return;
    }
    int id = _getId();
    _shutdow(id);
    m_isShutdown = true;
}

///////////////////////////////////////////////////////////////////////////
bool Local::Write(const uint8_t *buff, size_t count)
{
    int id = _getId();
    return _write(id, buff, count);
}

///////////////////////////////////////////////////////////////////////////
bool Local::Read(uint8_t *buff, size_t count)
{
    int id = _getId();
    return _read(id, buff, count);
}

///////////////////////////////////////////////////////////////////////////
bool Local::Peek(uint8_t *buff, size_t count)
{
    int id = _getId();
    return _peek(id, buff, count);
}

///////////////////////////////////////////////////////////////////////////
int Local::_getId() const
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    return m_id_;
}

///////////////////////////////////////////////////////////////////////////
void Local::_setId(int id)
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    m_id_ = id;
}

































///////////////////////////////////////////////////////////////////////////
bool IpV6::IsValid() const
{
    int id = _getId();
    if (m_isShutdown == true)
    {
        return false;
    }
    return id > 0;
}


///////////////////////////////////////////////////////////////////////////
bool IpV6::CanRead()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IpV6::CanWrite()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IpV6::CreateClient(const ServerAddress& address)
{
    int id = socket(AF_INET6, SOCK_STREAM, 0);

    if (id <= 0)
    {
        return false;
    }
    _setId(id);
    m_isShutdown = false;
    m_serverAddress = address;
    return true;
}

bool IpV6::_resolveServerAddress()
{
    // resolve
    _releaseServerAddress();
    auto& hostAddress = m_serverAddress.first;
    auto port = m_serverAddress.second;

    struct addrinfo hints;
    std::string portStr = std::to_string(port);

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET6;      /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;           /* Any protocol */

    if (getaddrinfo(hostAddress.c_str(), portStr.c_str(), &hints, &m_resolvedAddress))
    {
        _releaseServerAddress();
        return false;
    }
    return true;
}

void IpV6::_releaseServerAddress()
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    if(m_resolvedAddress != nullptr)
    {
        freeaddrinfo(m_resolvedAddress);
        m_resolvedAddress = nullptr;
    }
}

///////////////////////////////////////////////////////////////////////////
bool IpV6::ConnectToServer()
{
    if (IsValid() == false)
    {
        return false;
    }
    if (m_resolvedAddress == nullptr)
    {
        if (_resolveServerAddress() == false)
        {
            return false;
        }
    }

    int id = _getId();
    auto err = connect(id, m_resolvedAddress->ai_addr, m_resolvedAddress->ai_addrlen);
    if (err < 0)
    {
        ShutdownSocket();
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IpV6::CreateServer(ServerConfig cfg, int maxConnections)
{
    auto port = cfg;
    int id  = socket(AF_INET6, SOCK_STREAM, 0);
    if (id <= 0)
    {
        _setId(-1);
        return false;
    }
    _setId(id);
    m_isShutdown = false;
    int enable = 1;
    if (setsockopt(id, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        ShutdownSocket();
        CloseSocket();
        return false;
    }

    sockaddr_in6 servAddr;
    bzero((char *) &servAddr, sizeof(servAddr));

    servAddr.sin6_flowinfo = 0;
    servAddr.sin6_family = AF_INET6;
    memcpy(&servAddr.sin6_addr.s6_addr, &in6addr_any, sizeof(in6addr_any));
    servAddr.sin6_port = htons(port);

    int bindResult = bind(id, (struct sockaddr *) &servAddr, sizeof(servAddr));
    if (bindResult < 0)
    {
        ShutdownSocket();
        CloseSocket();
        return false;
    }
    if (listen(id, maxConnections))
    {
        ShutdownSocket();
        CloseSocket();
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IpV6::Listen(IpV6& newConnection)
{
    sockaddr_in6 cliAddr;
    socklen_t clilen = sizeof(cliAddr);
    int id = _getId();
    int result = accept( id, (struct sockaddr *) &cliAddr, &clilen);
    if (result < 0)
    {
        ShutdownSocket();
        newConnection._setId(-1);
        return false;
    }

    newConnection._setId(result);
    return true;
}

///////////////////////////////////////////////////////////////////////////
void IpV6::CloseSocket()
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    _close(m_id_);
    m_id_ = -1;
}

///////////////////////////////////////////////////////////////////////////
void IpV6::ShutdownSocket()
{
    if (IsValid() == false)
    {
        return;
    }
    _releaseServerAddress();
    int id = _getId();
    _shutdow(id);
    m_isShutdown = true;
}


///////////////////////////////////////////////////////////////////////////
bool IpV6::Write(const uint8_t *buff, size_t count)
{
    int id = _getId();
    return _write(id, buff, count);
}

///////////////////////////////////////////////////////////////////////////
bool IpV6::Read(uint8_t *buff, size_t count)
{
    int id = _getId();
    return _read(id, buff, count);
}

///////////////////////////////////////////////////////////////////////////
bool IpV6::Peek(uint8_t *buff, size_t count)
{
    int id = _getId();
    return _peek(id, buff, count);
}

///////////////////////////////////////////////////////////////////////////
int IpV6::_getId() const
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    return m_id_;
}

///////////////////////////////////////////////////////////////////////////
void IpV6::_setId(int id)
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    m_id_ = id;
}
















///////////////////////////////////////////////////////////////////////////
bool UdpV6Reader::IsValid() const
{
    int id = _getId();
    if (m_isShutdown == true)
    {
        return false;
    }
    return id > 0;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Reader::CanRead()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Reader::CanWrite()
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Reader::CreateClient(const ServerAddress& address)
{
    int id = socket(AF_INET6, SOCK_DGRAM, 0);

    if (id <= 0)
    {
        return false;
    }

    _setId(id);
    m_isShutdown = false;
    m_serverAddress = address;
    return true;
}

bool UdpV6Reader::_resolveServerAddress()
{
    _releaseServerAddress();
    auto& hostAddress = m_serverAddress.first;
    auto port = m_serverAddress.second;
    struct addrinfo hints;
    struct addrinfo*  localAddr = 0;         /* Local address to bind to */
    std::string portStr = std::to_string(port);

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    if (getaddrinfo(hostAddress.c_str(), portStr.c_str(), &hints, &m_resolvedAddress))
    {
        return false;
    }

    hints.ai_flags    = AI_PASSIVE;
    if ( getaddrinfo(NULL, portStr.c_str(), &hints, &localAddr) != 0 )
    {
        _releaseServerAddress();
        return false;
    }

    int enable = 1;
    int id = _getId();
    if (-1 == setsockopt(id, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(enable)))
    {
        _releaseServerAddress();
        freeaddrinfo(localAddr);
        return false;
    }

    if ( bind(id, localAddr->ai_addr, localAddr->ai_addrlen) != 0 )
    {
        _releaseServerAddress();
        freeaddrinfo(localAddr);
        return false;
    }
    freeaddrinfo(localAddr);
    return true;

}

void UdpV6Reader::_releaseServerAddress()
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    if(m_resolvedAddress != nullptr)
    {
        freeaddrinfo(m_resolvedAddress);
        m_resolvedAddress = nullptr;
    }
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Reader::ConnectToServer()
{
    if (IsValid() == false)
    {
        return false;
    }
    if (m_resolvedAddress == nullptr)
    {
        if (_resolveServerAddress() == false)
        {
            return false;
        }
    }

    struct ipv6_mreq multicastRequest;  /* Multicast address join structure */
    memcpy(&multicastRequest.ipv6mr_multiaddr,
       &((struct sockaddr_in6*)(m_resolvedAddress->ai_addr))->sin6_addr,
       sizeof(multicastRequest.ipv6mr_multiaddr));
    multicastRequest.ipv6mr_interface = 0;

    int id = _getId();
    if (0 != setsockopt(id, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, (char*) &multicastRequest, sizeof(multicastRequest)))
    {
        _releaseServerAddress();
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////
void UdpV6Reader::CloseSocket()
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    _close(m_id_);
    m_id_ = -1;
}

///////////////////////////////////////////////////////////////////////////
void UdpV6Reader::ShutdownSocket()
{
    if (IsValid() == false)
    {
        return;
    }
    _releaseServerAddress();
    int id = _getId();
    _shutdow(id);
    m_isShutdown = true;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Reader::Write(const uint8_t *buff, size_t count)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Reader::Read(uint8_t *buff, size_t count)
{
    int id = _getId();
    return _readUdp(id, buff, count);
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Reader::Peek(uint8_t *buff, size_t count)
{
    int id = _getId();
    return _peek(id, buff, count);
}

///////////////////////////////////////////////////////////////////////////
int UdpV6Reader::_getId() const
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    return m_id_;
}

///////////////////////////////////////////////////////////////////////////
void UdpV6Reader::_setId(int id)
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    m_id_ = id;
}

















///////////////////////////////////////////////////////////////////////////
bool UdpV6Writer::IsValid() const
{
    int id = _getId();
    if (m_isShutdown == true)
    {
        return false;
    }
    return id > 0;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Writer::CanRead()
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Writer::CanWrite()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Writer::CreateClient(const ServerAddress& address)
{
    m_serverAddress = address;
    if(false == _resolveServerAddress())
    {
        return false;
    }

    int id = socket(m_resolvedAddress->ai_family, m_resolvedAddress->ai_socktype, 0);
    if (id <= 0)
    {
        return false;
    }
    m_isShutdown = false;
    _setId(id);
    return true;
}

bool UdpV6Writer::_resolveServerAddress()
{
    _releaseServerAddress();
    auto& hostAddress = m_serverAddress.first;
    auto port = m_serverAddress.second;

    struct addrinfo hints = {0};

    hints.ai_family   = PF_INET6;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags    = AI_NUMERICHOST;
    std::string portStr = std::to_string(port);

    _releaseServerAddress();
    if (0 != getaddrinfo(hostAddress.c_str(), portStr.c_str(), &hints, &m_resolvedAddress))
    {
        return false;
    }
    return true;
}

void UdpV6Writer::_releaseServerAddress()
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    if(m_resolvedAddress != nullptr)
    {
        freeaddrinfo(m_resolvedAddress);
        m_resolvedAddress = nullptr;
    }
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Writer::ConnectToServer()
{
    if (IsValid() == false)
    {
        return false;
    }
    if (m_resolvedAddress == nullptr)
    {
        return false;
    }

    int ifindex = 0;
    int id = _getId();
    if (setsockopt(id, IPPROTO_IPV6, IPV6_MULTICAST_IF, &ifindex, sizeof(ifindex)) < 0)
    {
        ShutdownSocket();
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////
void UdpV6Writer::CloseSocket()
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    _close(m_id_);
    m_id_ = -1;
}

///////////////////////////////////////////////////////////////////////////
void UdpV6Writer::ShutdownSocket()
{
    if (IsValid() == false)
    {
        return;
    }
    _releaseServerAddress();
    int id = _getId();

    _shutdow(id);
    m_isShutdown = true;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Writer::Write(const uint8_t *buff, size_t count)
{
    int id = _getId();
    return _writeUdp(id, m_resolvedAddress, buff, count);
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Writer::Read(uint8_t *buff, size_t count)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool UdpV6Writer::Peek(uint8_t *buff, size_t count)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
int UdpV6Writer::_getId() const
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    return m_id_;
}

///////////////////////////////////////////////////////////////////////////
void UdpV6Writer::_setId(int id)
{
    std::lock_guard<std::mutex> locker(m_idLocker);
    m_id_ = id;
}














///////////////////////////////////////////////////////////////////////////
std::function<void(int)> ExecProcess::mGlobalSignalHadleAction;

ExecProcess::ExecProcess()
{
    mGlobalSignalHadleAction = [this](int signal) { _signalHandler(signal); };
    if (::signal(SIGINT, &ExecProcess::_globalSignalHandler) == SIG_ERR)
    {
        throw std::runtime_error("Can't handle child signals");
    }
}

ExecProcess::~ExecProcess()
{
    ShutdownSocket();
    CloseSocket();
}

bool ExecProcess::IsValid() const
{
    return m_isValid;
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::CanRead()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::CanWrite()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::CreateClient(const ServerAddress& address)
{
    if (pipe(m_childInId.data()) == 0)
    {
        if (pipe(m_childOutId.data()) == 0)
        {
            m_processName = address;
            m_isValid = true;
            return true;
        }
        else
        {
            // close file descriptors on fail
            close(m_childInId.at(0));
            close(m_childInId.at(1));
        }
    }

    // error
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::ConnectToServer()
{
    if (IsValid() == false)
    {
        return false;
    }

    if (false == _startProcess())
    {
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::CreateServer(ServerConfig cfg, int maxConnections)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::Listen(ExecProcess& newConnection)
{
    newConnection.m_isValid = false;
    return false;
}

///////////////////////////////////////////////////////////////////////////
void ExecProcess::CloseSocket()
{

}

///////////////////////////////////////////////////////////////////////////
void ExecProcess::ShutdownSocket()
{
    if (IsValid() == false)
    {
        return;
    }

    // Close used pipe descriptors
    _killProcess();
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::Write(const uint8_t *buff, size_t count)
{
    auto& parentOutWriteEnd = m_childInId[1];
    auto res = write(parentOutWriteEnd, buff, count);
    if (res < 0)
    {
        return false;
    }
    return (size_t)res == count;
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::Read(uint8_t *buff, size_t count)
{
    auto& parentInReadEnd = m_childOutId[0];
    auto res = read(parentInReadEnd, buff, count);
    if (res < 0)
    {
        return false;
    }
    return (size_t)res == count;
}

///////////////////////////////////////////////////////////////////////////
bool ExecProcess::Peek(uint8_t *buff, size_t count)
{
    ShutdownSocket();
    CloseSocket();
    return false;
}

void ExecProcess::_globalSignalHandler(int signal)
{
    mGlobalSignalHadleAction(signal);
}

void ExecProcess::_signalHandler(int signal)
{
    if (m_isValid && signal == SIGCHLD)
    {
        _killProcess();
    }
}

void ExecProcess::_killProcess()
{
    auto& parentOutWriteEnd = m_childInId[1];
    auto& parentInReadEnd = m_childOutId[0];

    close(parentOutWriteEnd);
    close(parentInReadEnd);

    ::kill(m_childId, SIGKILL);
    m_isValid = false;
}

bool ExecProcess::_startProcess()
{
    auto& childOutWriteEnd = m_childOutId[1];
    auto& childInReadEnd = m_childInId[0];

    auto& parentOutWriteEnd = m_childInId[1];
    auto& parentInReadEnd = m_childOutId[0];

    // Create child process
    m_childId = fork();
    if (m_childId == -1)
    {
        // std::cout << "Can't start process! Fork failed..." << std::endl;
        close(parentOutWriteEnd);
        close(parentInReadEnd);
        m_isValid = false;
        return false;
    }

    if (m_childId == 0)
    {
        bool hasError = false;
        // Duplicate pipe descriptors
        if (dup2(childInReadEnd , STDIN_FILENO) == -1)
        {
            hasError = true;
        }

        if (dup2(childOutWriteEnd,  STDOUT_FILENO) == -1)
        {
            hasError = true;
        }

        if (dup2(childOutWriteEnd,  STDERR_FILENO) == -1)
        {
            hasError = true;
        }

        // Close unused pipe descriptors
        if (close(parentInReadEnd) == -1)
        {
            hasError = true;
        }

        if (close(childInReadEnd) == -1)
        {
            hasError = true;
        }

        if (close(parentOutWriteEnd) == -1)
        {
            hasError = true;
        }

        if (close(childOutWriteEnd) == -1)
        {
            hasError = true;
        }

        // Try to start process
        if (!hasError && execl(m_processName.c_str(), "", (char *)nullptr) == -1)
        {
            hasError = true;
        }

        if (hasError)
        {
//             eCDebug(SIGNALS_CATEGORY) << "ExecProcess::_startProcess()";
            exit(-1);
        }
    }
    else
    {
        // Close unused pipe descriptors
        bool hasError = false;
        if (close(childInReadEnd) == -1)
        {
            //std::cout << "Close failed..." << std::endl;
            hasError = true;
        }

        if (close(childOutWriteEnd) == -1)
        {
            //std::cout << "Close failed..." << std::endl;
            hasError = true;
        }

        if (hasError)
        {
            _killProcess();
            return false;
        }
    }

    return true;
}

} //namespace Platform
} //namespace Sockets
