///////////////////////////////////////////////////////////////////////////
template<typename T1, typename T2>
std::string IBaseComponent::GetTypeName(const std::pair<T1, T2>&)
{
    std::string t1Name = GetTypeName(T1());
    std::string t2Name = GetTypeName(T2());

    return std::string("pair: ") + t1Name + std::string(" ") + t2Name;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
std::string IBaseComponent::GetTypeName(const std::vector<T>&)
{
    std::string tName = GetTypeName(T());


    return std::string("vector: ") + tName;
}

///////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValT>
std::string IBaseComponent::GetTypeName(const std::map<KeyT, ValT>&)
{
    std::string keyName = GetTypeName(KeyT());
    std::string valName = GetTypeName(ValT());

    return std::string("map: ") + keyName + std::string(" ") + valName;
}

///////////////////////////////////////////////////////////////////////////
template<typename T>
std::string IBaseComponent::GetTypeName()
{
    return GetTypeName(T());
}
