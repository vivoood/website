#include "IBaseComponent.h"
using namespace egt;


///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned long long&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_uint64");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed long long&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_int64");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned long&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_uint32");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed long&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_int32");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned short&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_uint16");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed short&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_int16");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned char&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_uint8");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed char&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_int8");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const unsigned&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_uint");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const signed&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_int");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const char&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    // 'unsigned char' and 'char' are two different C types.
    // 'char' is not guaranteed to have only 8 bits.
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_char");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const float&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_float");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const double&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_double");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const std::string&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_std::string");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const bool&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_bool");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}

///////////////////////////////////////////////////////////////////////////
u_int64_t IBaseComponent::GetTypeHash(const UniObject&, u_int32_t x, u_int32_t y, u_int32_t d)
{
    u_int64_t typeHash = HashConstructor::crc64("#NDN#_UniObj");
    return HashConstructor::ConstructHash(typeHash, x, y, d);
}
