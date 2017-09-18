namespace egt{
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template<typename Serializer, typename Deserializer>
template<typename T>
inline void GenericMsg<Serializer, Deserializer>::AddValue( const std::string& valueName, T&& value)
{
    Serializer serializer;
    serializer << std::forward<T>(value);
    m_values[valueName] = std::move(serializer.GetStorage());

}

///////////////////////////////////////////////////////////////////////////
template<typename Serializer, typename Deserializer>
template<typename T>
inline bool GenericMsg<Serializer, Deserializer>::GetValue( const std::string& valueName, T& value) const
{
    auto iter = m_values.find(valueName);
    if (iter == m_values.end())
    {
        return false;
    }
    const auto& buffer = iter->second;
    Deserializer deserializer(buffer);
    deserializer >> value;
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<typename Serializer, typename Deserializer>
std::vector<uint8_t> GenericMsg<Serializer, Deserializer>::Serialize() const
{
    Serializer serializer;
    serializer << *this;
    auto result = std::move(serializer.GetBuffer());
    return result;
}

///////////////////////////////////////////////////////////////////////////
template<typename Serializer, typename Deserializer>
bool GenericMsg<Serializer, Deserializer>::Deserialize(std::vector<uint8_t> &&buff)
{
    try
    {
        Deserializer deserializer(buff);
        deserializer >> *this;
    }
    catch(...)
    {
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<typename Serializer, typename Deserializer>
std::vector<std::string> GenericMsg<Serializer, Deserializer>::GetValueNames() const
{
    std::vector<std::string> names;
    for (const auto& p : m_values)
    {
        names.emplace_back(p.first);
    }
    return names;
}

///////////////////////////////////////////////////////////////////////////
template<typename Serializer, typename Deserializer>
bool GenericMsg<Serializer, Deserializer>::HasValue(const std::string &valueName) const
{
    return m_values.find(valueName) != m_values.end();
}


///////////////////////////////////////////////////////////////////////////
}
