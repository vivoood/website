#include "BashClient.h"
#include <lib_utils/Platform/PlatformSockets.h>
#include <string.h>
///////////////////////////////////////////////////////////////////////////

namespace egt{

namespace bash_client
{
//class StringLineProxy
//{
//public:
//    using SockImpl = Platform::Sockets::ExecProcess;
//    using ServerAddress = SockImpl::ServerAddress;
//    using ServerConfig = SockImpl::ServerConfig;
//    //
//    bool IsValid() const;
//    static bool CanRead();
//    static bool CanWrite();
//    //
//    bool CreateClient(const ServerAddress& address);
//    //
//    bool ConnectToServer();
//    //
//    //
//    bool CreateServer(ServerConfig cfg, int maxConnections = 256);
//    //
//    bool Listen(StringLineProxy& newConnection);
//    //
//    void Close();
//    //
//    bool Write(const uint8_t *buff, size_t count);
//    bool Read(uint8_t *buff, size_t count);
//    bool Peek(uint8_t *buff, size_t count);

//private:
//    ServerAddress m_address;
//    SockImpl m_sockImpl;

//    std::mutex m_dataLocker;
//    std::queue<std::string> m_readyData;
//};


///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::IsValid() const
{
    return m_sockImpl.IsValid();
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::CanRead()
{
    return SockImpl::CanRead();
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::CanWrite()
{
    return SockImpl::CanRead();
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::CreateClient(const ServerAddress& address)
{
    return m_sockImpl.CreateClient(address);
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::ConnectToServer()
{
    return m_sockImpl.ConnectToServer();
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::CreateServer(ServerConfig cfg, int maxConnections)
{
    return m_sockImpl.CreateServer(cfg, maxConnections);
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::Listen(StringLineProxy& newConnection)
{
    return m_sockImpl.Listen(newConnection.m_sockImpl);
}

void StringLineProxy::ShutdownSocket()
{
    m_sockImpl.ShutdownSocket();
}

///////////////////////////////////////////////////////////////////////////
void StringLineProxy::CloseSocket()
{
    m_sockImpl.CloseSocket();
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::Write(const uint8_t *buff, size_t count)
{
    return m_sockImpl.Write(buff + NetMsg::GetHeaderSize(), count - NetMsg::GetHeaderSize() - 1);
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::Read(uint8_t *buff, size_t count)
{
    std::unique_lock<std::mutex> locker(m_dataLocker);
    bool isEmpty = m_readyData.empty();
    std::string str = isEmpty ? "" : m_readyData.front();
    if (isEmpty == false)
    {
        m_readyData.pop();
    }
    locker.unlock();

    if (isEmpty == true)
    {
        return false;
    }

    auto headerSize = NetMsg::GetHeaderSize();
    if (count != str.size() + headerSize + 1)
    {
        return false;
    }


    NetMsg::Header fakeHeader;
    fakeHeader.channel = 0;
    fakeHeader.payloadSize = str.size() + 1;
    auto rawHeader = NetMsg::SerializeHeader(fakeHeader);
    memcpy(buff, rawHeader.data(), headerSize);
    memcpy(buff + headerSize, str.c_str(), str.size());
    buff[count-1] = 1; // msg marker
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool StringLineProxy::Peek(uint8_t *buff, size_t count)
{
    auto headerSize = NetMsg::GetHeaderSize();
    if (count != headerSize)
    {
        // ASSERT
        return false;
    }

    std::unique_lock<std::mutex> locker(m_dataLocker);
    bool isEmpty = m_readyData.empty();
    uint32_t strSize = isEmpty ? 0 : m_readyData.front().size();
    locker.unlock();

    if (m_readyData.empty() == true)
    {
        std::string newStr;
        while(true)
        {
            uint8_t c;
            auto result = m_sockImpl.Read(&c, 1);
            if (result == false)
            {
                return false;
            }
            newStr.push_back(c);
            if (c == '\n')
            {
                locker.lock();
                m_readyData.push(newStr);
                locker.unlock();
                strSize = newStr.size();
                break;
            }
        }
    }
    NetMsg::Header fakeHeader;
    fakeHeader.channel  = 0;
    fakeHeader.payloadSize = strSize + 1;
    std::vector<uint8_t> headerBuff = NetMsg::SerializeHeader(fakeHeader);
    memcpy(buff, headerBuff.data(), count);
    return true;
}

} // namespace egt

} //namespace bash_client
