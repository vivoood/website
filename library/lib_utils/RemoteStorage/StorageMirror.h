#ifndef __STORAGE_MIRROR__
#define __STORAGE_MIRROR__


#include <functional>
#include <vector>
#include <memory>
#include <string.h>
#include <mutex>
#include <egt_lib/debug/egt_debug.h>

#include "StorageMgrClient.h"

namespace egt {
namespace RemoteStorage
{
class StorageMirror final
{
private:
    struct Locker{};
public:
    using Ptr = std::shared_ptr<StorageMirror>;
    using WeakPtr = std::weak_ptr<StorageMirror>;
    struct Transaction
    {
        Transaction(Transaction&&)                    = default;
        Transaction& operator= ( Transaction&& )      = default;
        //
        Transaction(const Transaction&)               = delete;
        Transaction& operator= (const Transaction&)   = delete;

        template<typename ValueType>
        Transaction& WriteGameValue(const ValueType& value, const std::string& paramKey, int gameId);
        template<typename ValueType>
        Transaction& WriteValue(const ValueType& value, const std::string& paramKey);
        Transaction& WriteBinaryValue(const uint8_t* src, const std::string& paramKey, size_t offset, size_t size);

        ~Transaction();
        bool Save();
        void Cancel();

    private:
        Transaction(StorageMirror::WeakPtr mirror) : m_mirror(mirror){}
        //
        bool m_isFinished = false;
        StorageMirror::WeakPtr m_mirror;
        std::vector<WriteRequest> m_requests;

        friend class StorageMirror;
    };

    ///////////////////////////////////////////////////////////////////////
    static Ptr CreateInstance(Locker, Client::WeakPtr clientPtr);
    StorageMirror(Locker, Client::WeakPtr clientPtr) : m_client(clientPtr){}
    StorageMirror(StorageMirror&&)                    = default;
    StorageMirror& operator= ( StorageMirror&& )      = default;
    //
    StorageMirror(const StorageMirror&)               = delete;
    StorageMirror& operator= (const StorageMirror&)   = delete;
    ~StorageMirror() = default;

    bool IsParamSet(const std::string& paramKey) const;
    bool IsGameParamSet(const std::string& paramKey, int gameId) const;

    template<typename ValueType>
    bool ReadValue(ValueType& value, const std::string& paramKey) const;

    template<typename ValueType>
    bool ReadGameValue(ValueType& value, const std::string& paramKey, int gameId) const;

    ParameterInfo GetParameterInfo(const std::string& paramKey) const;
    ParameterInfo GetGameParameterInfo(const std::string& paramKey, int gameId) const;

    StorageMirror& RegisterParam(const std::string& paramKey);
    StorageMirror& RegisterGameParam(const std::string& paramKey, int gameId);
    void OnChange(const std::vector<WriteRequest>& changes);
    void RefreshParams();
    Transaction GetTransaction();
    void SetOnChangeCallback(std::function<void()> callback, std::weak_ptr<void> sentinel);

    // Returns { gameId, paramId }
    std::vector<std::pair<int, std::string>> GetAllParams() const;

private:
    bool ApplyWriteRequests(const std::vector<WriteRequest>& requests);
    std::weak_ptr<StorageMirror> m_ownPtr;
    Client::WeakPtr m_client;
    std::vector<ReadRequest> m_readRequests;
    using GameContainer = std::map<std::string, ReadResult>;
    std::map<int, GameContainer> m_values;
    mutable std::mutex m_storageLocker;
    std::pair<std::weak_ptr<void>, std::function<void()>> m_onChangeCallback = {};
    //
    friend class egt::RemoteStorage::Client;
    friend struct StorageMirror::Transaction;
};


//////////////////////////////////////////////////////////////////////////////////////////
template<typename ValueType>
StorageMirror::Transaction& StorageMirror::Transaction::WriteGameValue(const ValueType& value, const std::string& paramKey, int gameId)
{
    if (m_isFinished)
    {
        throw ("Using finished transaction.");
    }
    WriteRequest request;
    request.dataKey = paramKey;
    request.gameId = gameId;
    request.offset = 0;
    request.isGameParam = true;
    request.data.resize(sizeof(ValueType));
    const uint8_t* src = reinterpret_cast<const uint8_t*>(&value);
    memcpy(request.data.data(), src, sizeof(ValueType));
    m_requests.push_back(std::move(request));
    return *this;
}

template<typename ValueType>
StorageMirror::Transaction& StorageMirror::Transaction::WriteValue(const ValueType& value, const std::string& paramKey)
{
    if (m_isFinished)
    {
        throw ("Using finished transaction.");
    }
    WriteRequest request;
    request.dataKey = paramKey;
    request.gameId = -1;
    request.offset = 0;
    request.isGameParam = false;
    request.data.resize(sizeof(ValueType));
    const uint8_t* src = reinterpret_cast<const uint8_t*>(&value);
    memcpy(request.data.data(), src, sizeof(ValueType));
    m_requests.push_back(std::move(request));
    return *this;
}

template<typename ValueType>
bool StorageMirror::ReadGameValue(ValueType& value, const std::string& paramKey, int gameId) const
{
    std::lock_guard<std::mutex> lock(m_storageLocker);
    auto gameIt = m_values.find(gameId);
    if (gameIt == m_values.end()) {
        eCDebug(LOG_CATEGORY_STORAGE) << "StorageMirror::ReadGameValue: gameIt == m_values.end() - " << paramKey;
        return false;
    }
    const auto& gameContainer = gameIt->second;
    auto valueIt = gameContainer.find(paramKey);
    if (valueIt == gameContainer.end()) {
        eCDebug(LOG_CATEGORY_STORAGE) << "StorageMirror::ReadGameValue: valueIt == gameContainer.end() - " << paramKey;
        return false;
    }
    const auto& readResult = valueIt->second;
    if (readResult.isOk == false) {
        eCDebug(LOG_CATEGORY_STORAGE) << "StorageMirror::ReadGameValue: readResult.isOk == false - " << paramKey;
        return false;
    }
    if (readResult.data.size() != sizeof(ValueType))
    {
        // ASSERT
        throw("Different parameter size.");
    }
    uint8_t* dst = reinterpret_cast<uint8_t*>(&value);
    memcpy(dst, readResult.data.data(), sizeof(ValueType));
    return true;
}

template<typename ValueType>
bool StorageMirror::ReadValue(ValueType& value, const std::string& paramKey) const
{
    return ReadGameValue(value, paramKey, -1);
}

}}

#endif // __STORAGE_MIRROR__
