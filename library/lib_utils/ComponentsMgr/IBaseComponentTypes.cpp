#include "IBaseComponent.h"
#include "../Crc.h"
using namespace egt;


///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const unsigned long long&)
{
    return "uint64";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const signed long long&)
{
    return "int64";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const unsigned long&)
{
    return "uint32";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const signed long&)
{
    return "int32";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const unsigned short&)
{
    return "uint16";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const signed short&)
{
    return "int16";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const unsigned char&)
{
    return "uint8";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const signed char&)
{
    return "int8";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const unsigned&)
{
    return "uint";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const signed&)
{
    return "int";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const char&)
{
    return "char";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const float&)
{
    return "float";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const double&)
{
    return "double";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const std::string&)
{
    return "string";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const bool&)
{
    return "bool";
}

///////////////////////////////////////////////////////////////////////////
std::string IBaseComponent::GetTypeName(const UniObject&)
{
    return "UniObj";
}
