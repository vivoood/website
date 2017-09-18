#ifndef __STORAGE_MGR_SERVICE_SERVER__
#define __STORAGE_MGR_SERVICE_SERVER__


#include <functional>
#include <vector>
#include <memory>
#include <future>
#include <atomic>
#include <lib_utils/Network/Messengers/Messenger.h>
#include <lib_utils/UniObject/UniMsg.h>
#include "StorageMgrCommon.h"
#include <mutex>

namespace egt {
namespace RemoteStorage
{

class Server final
{
public:
    using TransactionId = uint32_t;
    using ConnectionId = int;
    using GameId = int;
   // pram setter types
    using WriterHandler = std::function<bool(std::vector<WriteRequest>& writeRequest)>;
    using ReaderHandler = std::function<std::vector<ReadResult>(std::vector<ReadRequest>& readRequest)>;

    using WaitResult = IConnection::WaitResult;
    using Duration = std::chrono::milliseconds;

    ///////////////////////////////////////////////////////////////////////
    Server();
    ~Server();
    void Stop();

    void Init(IConnector::Ptr connector, WriterHandler writer, ReaderHandler reader);
    //
    void WriteDataCallback(uint32_t transactionId, WriteRequest request);
    void FlushTransactionCallback(uint32_t transactionId);
    void CancelTransactionCallback(uint32_t transactionId);

    ///////////////////////////////////////////////////////////////////////

private:
    void _write(NetworkPromise<UniMsg> promise);
    void _read(NetworkPromise<UniMsg> promise);

    void _requestHandler(NetworkPromise<UniMsg> promise);
    void _onMsgReceived(int connectionId, UniMsg& msg);
    void _registerParam(int connectionId, const std::string& paramId);
    void _registerGameParam(int connectionId, const std::string& paramId, int gameId);
    void _cleanupConnection(int connectionId);
    //void AssertHandler(FutureConnection::Asserts assertType);

    // param setters
    WriterHandler m_writer = nullptr;
    ReaderHandler m_reader = nullptr;

    std::atomic<bool> m_isAlive{false};
    std::thread m_process;
    Messenger<UniMsg> m_net;

    using GameParams = std::map<GameId, std::set<std::string>>;
    std::mutex m_paramsLocker;
    std::map<ConnectionId, GameParams> m_paramsPerConnection;
    std::map<TransactionId, std::map<ConnectionId, std::vector<WriteRequest>>> m_pendingChanges;
};

}}

#endif // __STORAGE_MGR_SERVICE_SERVER__
