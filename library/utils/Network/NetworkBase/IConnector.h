#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include <thread>
#include <mutex>
#include "memory"
//
#include "IConnection.h"

namespace egt{

class IConnector
{
public:
    using Duration = IConnection::Duration;
    using Timepoint = std::chrono::system_clock::time_point;
    using Ptr = std::shared_ptr<IConnector>;
    using WeakPtr = std::weak_ptr<IConnector>;

    enum class ConnectionResult
    {
        ConnectionOK,
        Timeout,
        Error,
    };

protected:
    virtual IConnection::Ptr _waitForConnection(Timepoint waitUntil) = 0;
    virtual void _stop() = 0;
    //
    void _onNewEventCallback();
    void _setThreadName(std::thread& thread, const std::string& threadName);
public:
    IConnector();
    virtual ~IConnector() = default;
    IConnection::Ptr WaitForConnection(Duration timeout = Duration(0));
    IConnection::Ptr CheckForConnection();
    IConnection::Ptr BlockForConnection();
    void SetEventCallback(std::function<void()> callback);
    void Stop();
    std::string GetName() const;
    void SetName(const std::string& name);
private:
    std::function<void()> m_newEventCallback;
    std::string m_name;
    uint64_t m_baseId;
    static std::mutex s_idLocker;
    static uint64_t s_id;
};

}
#endif // ICONNECTOR_H
