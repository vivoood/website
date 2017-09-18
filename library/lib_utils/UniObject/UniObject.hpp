
///////////////////////////////////////////////////////////////////////////
template<typename ValueType>
egt::UniObject::UniObject(const ValueType& obj) // copy
{
    egt::oUniStream stream;
    stream << obj;
    m_data = std::move(stream.GetBuffer());
}

///////////////////////////////////////////////////////////////////////////
template<typename ValueType>
egt::UniObject::UniObject(ValueType&& obj) // move
{
    egt::oUniStream stream;
    stream << obj;
    m_data = std::move(stream.GetBuffer());
}

///////////////////////////////////////////////////////////////////////////
template<typename ValueType>
const std::vector<unsigned char>& egt::UniObject::operator <<(const ValueType& v)
{
    egt::oUniStream stream;
    stream << v;
    m_data = std::move(stream.GetBuffer());
    return m_data;
}

///////////////////////////////////////////////////////////////////////////
template<typename ValueType>
void egt::UniObject::operator >>(ValueType& v) const
{
    const auto& data = m_data;
    egt::iUniStream iStream(data);
    iStream >> v;
}


