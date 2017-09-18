#ifndef __STORAGE_MGR_SERVICE_CLIENT__
#define __STORAGE_MGR_SERVICE_CLIENT__


#include <functional>
#include <vector>
#include <memory>
#include <mutex>

#include <lib_utils/Network/Messengers/Messenger.h>
#include <lib_utils/UniObject/UniMsg.h>

#include "StorageMgrCommon.h"

namespace egt {
namespace RemoteStorage
{

class StorageMirror;

class Client final
{
private:
    struct Locker{};
public:
    using StorageMirrorPtr = std::shared_ptr<StorageMirror>;
    using StorageMirrorWeakPtr = std::weak_ptr<StorageMirror>;
    using Ptr = std::shared_ptr<Client>;
    using WeakPtr = std::weak_ptr<Client>;
    using WaitResult = IConnection::WaitResult;
    using Duration = std::chrono::milliseconds;

    ///////////////////////////////////////////////////////////////////////

    static Ptr CreateInstance();

    Client(Locker);
    ~Client();
    void Stop();

    void Init(IConnector::Ptr connector);
    void Process();

    ///////////////////////////////////////////////////////////////////////

    bool Write(std::vector<WriteRequest>& requests);
    std::vector<ReadResult> Read(std::vector<ReadRequest>& requests);
    bool WaitForConnection(Duration timeout);
    StorageMirrorPtr CreateStorageMirror();
    void RegisterParam(const std::string& paramKey, StorageMirrorWeakPtr mirrorWeak);
    void RegisterGameParam(const std::string& paramKey, int gameId, StorageMirrorWeakPtr mirrorWeak);
private:
    void _msgHandler(int connectionId, UniMsg& promise);
    bool _processWriteResult(UniMsg &msg);
    void _onConnect(int connectionId);
    void _onDisconnect(int connectionId);
    void _onChange(const std::vector<WriteRequest>& changes);
    void _cleanupMirrors();
    struct Parameter
    {
        std::string key;
        int gameId;
        std::vector<uint8_t> data;
    };

    Messenger<UniMsg> m_net;

    std::recursive_mutex m_netLocker;
    std::weak_ptr<Client> m_ownPtr;

    using MirrorsPerParam = std::map<std::string, std::vector<StorageMirrorWeakPtr>>;
    std::map<int, MirrorsPerParam> m_mirrorsPerParam;
    std::vector<UniMsg> m_registrationMessages;
    int m_serverConnectionId = -1;
};

}}

#endif // __STORAGE_MGR_SERVICE_CLIENT__
