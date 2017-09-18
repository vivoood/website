#ifndef LocalCONNECTION_H
#define LocalCONNECTION_H
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "../NetworkBase/IConnection.h"

namespace egt{

class LocalConnection : public IConnection
{
public:
    LocalConnection(const LocalConnection&) = delete;
    LocalConnection(LocalConnection&&) = delete;
    void operator=(const LocalConnection&) = delete;
    //
    LocalConnection();
    virtual ~LocalConnection();
    void Init(std::weak_ptr<LocalConnection> remote);
    static void Start(std::shared_ptr<LocalConnection> c1, std::shared_ptr<LocalConnection> c2);
    //
    int id = 0;
protected:
    WaitResult _waitForMsg(Timepoint waitUntil) final;
    bool _waitForDisconnect(Timepoint waitUntil) final;
    //
    NetMsg _getMsg() final;
    SendResult _sendMsg(NetMsg&& netMsg) final;
    void _disconnect() final;
private:
    void _startNotifier();
    void _notifyRemoteConnection();
    void _remoteNotificatorLoop();
    std::weak_ptr<LocalConnection> m_remote;
    //
    std::queue<NetMsg> m_incomming;
    //
    std::mutex m_lockerIn;
    std::mutex m_lockerDisconnect;
    //
    std::condition_variable m_inEvent;
    std::condition_variable m_disconnectEvent;
    std::atomic<bool> m_isConnected{false};
    //
    std::condition_variable m_removeNotificatorEvent;
    std::mutex m_removeNotificatorLocker;
    std::atomic<bool> m_shouldNotify;
    std::atomic<bool> m_shouldExit;
    std::thread m_remoteNotificator;
};

}
#endif // LocalCONNECTION_H
