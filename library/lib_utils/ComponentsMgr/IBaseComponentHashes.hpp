///////////////////////////////////////////////////////////////////////////
template<typename T1, typename T2>
u_int64_t IBaseComponent::GetTypeHash(const std::pair<T1, T2>&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t t1Hash = GetTypeHash(T1(), x+997, y, d+991);
    u_int64_t t2Hash = GetTypeHash(T2(), x, y+983, d+977);

    u_int64_t hash = HashConstructor::ConstructHash(t1Hash, t2Hash);

    return hash;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
u_int64_t IBaseComponent::GetTypeHash(const std::vector<T>&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t hash = GetTypeHash(T(), x+104729, y+104723, d+104717);
    return hash;
}

///////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValT>
u_int64_t IBaseComponent::GetTypeHash(const std::map<KeyT, ValT>&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t t1Hash = GetTypeHash(KeyT(), x+1299827, y, d+1299821);
    u_int64_t t2Hash = GetTypeHash(ValT(), x, y+1299817, d+1299811);

    u_int64_t hash = HashConstructor::ConstructHash(t1Hash, t2Hash);

    return hash;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
u_int64_t IBaseComponent::GetFieldHash(const char* fieldName, int fieldPos, bool isRequired)
{
    u_int64_t typeHash = GetTypeHash(T(), 97, 89, 83);
    u_int64_t hash = HashConstructor::ConstructHash(typeHash, fieldName, (u_int32_t)fieldPos, isRequired);
    return hash;
}
