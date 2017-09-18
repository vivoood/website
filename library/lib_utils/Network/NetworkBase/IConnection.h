#ifndef ICONNECTION_H
#define ICONNECTION_H

#include <cinttypes>
#include <functional>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
//
#include "NetMsg.h"
namespace egt{

class IConnection
{
public:
    using Duration = std::chrono::milliseconds;
    using Timepoint = std::chrono::system_clock::time_point;
    using Ptr = std::shared_ptr<IConnection>;
    using WeakPtr = std::weak_ptr<IConnection>;

    enum class WaitResult
    {
        NewMsg,
        NoMsg,
        Disconnected,
        Error
    };
    enum class SendResult
    {
        SendOk,
        Disconnected,
        Error
    };

protected:
    virtual WaitResult _waitForMsg(Timepoint waitUntil) = 0;
    virtual bool _waitForDisconnect(Timepoint waitUntil) = 0;
    //
    virtual NetMsg _getMsg() = 0;
    virtual SendResult _sendMsg(NetMsg&& netMsg) = 0;
    virtual void _disconnect() = 0;
    //
    void _onNewEventCallback();
    void _setThreadName(std::thread& thread, const std::string& threadName);
public:
    IConnection();
    virtual ~IConnection() = default;

    WaitResult WaitForMsg(Duration timeout);
    WaitResult WaitForMsgUntil(Timepoint timepoint);
    WaitResult CheckForMsg();
    WaitResult BlockForMsg();
    NetMsg GetMsg();
    //
    bool WaitForDisconnect(Duration timeout);
    bool WaitForDisconnectUntil(Timepoint timepoint);
    bool CheckForDisconnect();
    bool BlockForDisconnect();
    //
    SendResult SendMsg(NetMsg&& netMsg);
    void Disconnect();
    //
    void SetEventCallback(std::function<void()> callback);
    std::string GetName() const;
    void SetName(const std::string& name);
private:
    std::function<void()> m_newEventCallback;
    std::string m_name;
    uint64_t m_baseId = 0;
    static std::mutex s_idLocker;
    std::mutex s_fnLocker;
    static uint64_t s_id;
};

}

#endif // ICONNECTION_H
