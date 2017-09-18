#include "StorageMirror.h"

namespace egt {
namespace RemoteStorage
{

StorageMirror& StorageMirror::RegisterGameParam(const std::string &paramKey, int gameId)
{
    auto client = m_client.lock();
    if (client == nullptr)
    {
        return *this;
    }

    for (auto& request : m_readRequests)
    {
        if (request.dataKey == paramKey && request.gameId == gameId)
        {
            return *this;
        }
    }
    ReadRequest readRequest;
    readRequest.dataKey = paramKey;
    readRequest.gameId = gameId;
    readRequest.isGameParam = true;
    m_readRequests.emplace_back(std::move(readRequest));

    client->RegisterGameParam(paramKey, gameId, m_ownPtr);
    return *this;
}

StorageMirror::Ptr StorageMirror::CreateInstance(StorageMirror::Locker, Client::WeakPtr clientPtr)
{
    auto ptr = std::make_shared<StorageMirror>(Locker(), clientPtr);
    ptr->m_ownPtr = ptr;
    return ptr;
}

bool StorageMirror::IsParamSet(const std::string &paramKey) const
{
    return IsGameParamSet(paramKey, -1);
}

bool StorageMirror::IsGameParamSet(const std::string &paramKey, int gameId) const
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
    return readResult.isOk;
}

ParameterInfo StorageMirror::GetParameterInfo(const std::string &paramKey) const
{
    return GetGameParameterInfo(paramKey, -1);
}

ParameterInfo StorageMirror::GetGameParameterInfo(const std::string &paramKey, int gameId) const
{
    ParameterInfo info;
    info.gameId = gameId;
    info.isGameParam = (gameId > -1);
    const auto paramsIt = m_values.find(gameId);
    if (paramsIt == m_values.end())
    {
        info.isOk = false;
        info.paramtereSize = 0;
        return info;
    }
    const auto& params = paramsIt->second;
    const auto paramIt = params.find(paramKey);
    if (paramIt == params.end())
    {
        info.isOk = false;
        info.paramtereSize = 0;
        return info;
    }
    const auto& param = paramIt->second;
    info.isOk = param.isOk;
    info.paramtereSize = param.data.size();
    info.isSetupOnce = param.isSetupOnce;
    return info;
}

void StorageMirror::OnChange(const std::vector<WriteRequest> &changes)
{
    ApplyWriteRequests(changes);
    // call callback
    auto& sentinel = m_onChangeCallback.first;
    auto& callback = m_onChangeCallback.second;
    auto locker = sentinel.lock();
    if (nullptr != locker)
    {
        callback();
    }
}

StorageMirror& StorageMirror::RegisterParam(const std::string &paramKey)
{
    auto client = m_client.lock();
    if (client == nullptr)
    {
        return *this;
    }

    for (auto& request : m_readRequests)
    {
        if (request.dataKey == paramKey)
        {
            return *this;
        }
    }
    ReadRequest readRequest;
    readRequest.dataKey = paramKey;
    readRequest.gameId = -1;
    readRequest.isGameParam = false;
    m_readRequests.emplace_back(std::move(readRequest));

    client->RegisterParam(paramKey, m_ownPtr);
    return *this;
}

void StorageMirror::RefreshParams()
{
    auto client = m_client.lock();
    if (nullptr == client)
    {
        return;
    }
    auto readResults = client->Read(m_readRequests);
    //
    std::lock_guard<std::mutex> lock(m_storageLocker);
    m_values.clear();
    for (auto readResult : readResults)
    {
        auto& gameContainer = m_values[readResult.gameId];
        gameContainer[readResult.dataKey] = readResult;
    }
}

StorageMirror::Transaction StorageMirror::GetTransaction()
{
    Transaction transaction(m_ownPtr);
    return transaction;
}

void StorageMirror::SetOnChangeCallback(std::function<void ()> callback, std::weak_ptr<void> sentinel)
{
    m_onChangeCallback = {sentinel, callback};
}

std::vector<std::pair<int, std::string> > StorageMirror::GetAllParams() const
{
    std::vector<std::pair<int, std::string>> result;
    for (const auto& p : m_values)
    {
       int gameId = p.first;
       const auto& params = p.second;
       for (const auto& param : params)
       {
           const auto& paramName = param.first;
           result.push_back({gameId, paramName});
       }
    }
    return result;
}

bool StorageMirror::ApplyWriteRequests(const std::vector<WriteRequest> &requests)
{
    std::lock_guard<std::mutex> lock(m_storageLocker);
    // Check all first
    for (const auto& request : requests)
    {
        auto gameId = request.gameId;
        if (request.isGameParam == false)
        {
            gameId = -1;
        }
        auto gameIt = m_values.find(gameId);
        if (gameIt == m_values.end())
        {
            return false;
        }
        auto& gameContainer = gameIt->second;
        auto valueIt = gameContainer.find(request.dataKey);
        if (valueIt == gameContainer.end())
        {
            return false;
        }
        auto& value = valueIt->second;
        if (request.offset + request.data.size() > value.data.size())
        {
            value.data.resize(request.offset + request.data.size());
        }
    }
    // Save values
    for (const auto& request : requests)
    {
        auto gameId = request.gameId;
        if (request.isGameParam == false)
        {
            gameId = -1;
        }
        auto& gameContainer = m_values[gameId];
        auto& value = gameContainer[request.dataKey];
        size_t offset = request.offset;
        value.isOk = true;
        memcpy(value.data.data()+offset, request.data.data(), request.data.size());
    }
    return true;
}

StorageMirror::Transaction& StorageMirror::Transaction::WriteBinaryValue(const uint8_t *src, const std::string &paramKey, size_t offset, size_t size)
{
    if (m_isFinished)
    {
        throw ("Using finished transaction.");
    }
    WriteRequest request;
    request.dataKey = paramKey;
    request.gameId = -1;
    request.isGameParam = false;
    request.offset = offset;
    request.data.resize(size);
    memcpy(request.data.data(), src, size);
    m_requests.push_back(std::move(request));
    return *this;
}

StorageMirror::Transaction::~Transaction()
{
    if (m_isFinished == false)
    {
        Save();
    }
}

bool StorageMirror::Transaction::Save()
{
    m_isFinished = true;
    auto requests = std::move(m_requests);
    m_requests = std::vector<WriteRequest>();

    auto mirror = m_mirror.lock();
    if (mirror == nullptr)
    {
        eCDebug(LOG_CATEGORY_STORAGE) << "Transaction::Save: mirror == nullptr";
        return false;
    }
    auto client = mirror->m_client.lock();
    if (client == nullptr)
    {
        eCDebug(LOG_CATEGORY_STORAGE) << "Transaction::Save: client == nullptr";
        return false;
    }
    auto result = client->Write(requests);
    return result;
}

void StorageMirror::Transaction::Cancel()
{
    m_isFinished = true;

    m_requests.clear();
}




}}
