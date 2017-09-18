#include "UniObject.h"

using namespace egt;
namespace egt
{
///////////////////////////////////////////////////////////////////////////
UniObject UniObject::Create(std::vector<unsigned char> &buff)
{
    UniObject res;
    res.SetBuffer(buff);
    return res;
}

UniObject::UniObject()
    : m_data(std::vector<unsigned char>())
{}

///////////////////////////////////////////////////////////////////////////
UniObject::UniObject(const UniObject& obj) // copy
    : m_data(obj.m_data)
{}

///////////////////////////////////////////////////////////////////////////
UniObject& UniObject::operator=(const UniObject& obj) // copy assignment
{
    m_data = obj.m_data;
    return *this;
}

///////////////////////////////////////////////////////////////////////////
UniObject::UniObject(UniObject&& obj) // move
    : m_data(std::move(obj.m_data))
{}

///////////////////////////////////////////////////////////////////////////
UniObject& UniObject::operator=(UniObject&& obj) // move assignment
{
    m_data = std::move(obj.m_data);
    return *this;
}

///////////////////////////////////////////////////////////////////////////
bool UniObject::operator !=(const UniObject &obj) const
{
    return (GetBuffer() != obj.GetBuffer());
}

///////////////////////////////////////////////////////////////////////////
bool UniObject::operator ==(const UniObject &obj) const
{
    return (GetBuffer() == obj.GetBuffer());
}

///////////////////////////////////////////////////////////////////////////
const std::vector<unsigned char>& UniObject::GetBuffer() const
{
    return m_data;
}

///////////////////////////////////////////////////////////////////////////
void UniObject::SetBuffer(std::vector<unsigned char> &buff)
{
    m_data = std::move(buff);
}

///////////////////////////////////////////////////////////////////////////
void UniObject::SetConstBuffer(const std::vector<unsigned char> &buff)
{
    m_data = buff;
}

///////////////////////////////////////////////////////////////////////////
egt::oUniStream& operator<< (egt::oUniStream& out, const egt::UniObject& obj)
{
    out << obj.GetBuffer();
    return out;
}

///////////////////////////////////////////////////////////////////////////
egt::iUniStream& operator>> (egt::iUniStream& in, egt::UniObject& obj)
{
    std::vector<unsigned char> buff;
    in >> buff;
    obj.SetBuffer(buff);
    return in;
}
}
