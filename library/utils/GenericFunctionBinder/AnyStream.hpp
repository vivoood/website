#ifndef _ANY_STREAM_H_
#define _ANY_STREAM_H_

#include <../nonstd/any.hpp>
#include <queue>

namespace nonstd
{
namespace detail
{
//Non-convertible fallback
template<typename From, typename To, typename std::enable_if<!std::is_convertible<From, To>::value>::type* = nullptr>
constexpr To implicit_cast_impl(const nonstd::any&)
{
    To fallback{};
    return fallback;
}

//Convertible implicit cast
template<typename From, typename To, typename std::enable_if<std::is_convertible<From, To>::value>::type* = nullptr>
constexpr To implicit_cast_impl(const nonstd::any& operand)
{
    return static_cast<To>(nonstd::any_cast<From>(operand));
}


//Non-convertible fallback
template<typename From, typename To, typename std::enable_if<!std::is_convertible<From, To>::value>::type* = nullptr>
constexpr bool can_implicit_cast_impl(const nonstd::any&)
{
    return false;
}

//Convertible implicit cast
template<typename From, typename To, typename std::enable_if<std::is_convertible<From, To>::value>::type* = nullptr>
constexpr bool can_implicit_cast_impl(const nonstd::any& operand)
{
    return (operand.type() == rtti::type_id<From>());
}


//Try to implicit cast an 'any' parameter to a type T
template<typename To>
To implicit_cast(const nonstd::any& operand)
{
    if (can_implicit_cast_impl<To, To>(operand))
    {
        return implicit_cast_impl<To, To>(operand);
    }
    else if (can_implicit_cast_impl<std::int8_t, To>(operand))
    {
        return implicit_cast_impl<std::int8_t, To>(operand);
    }
    else if (can_implicit_cast_impl<std::int16_t, To>(operand))
    {
        return implicit_cast_impl<std::int16_t, To>(operand);
    }
    else if (can_implicit_cast_impl<std::int32_t, To>(operand))
    {
        return implicit_cast_impl<std::int32_t, To>(operand);
    }
    else if (can_implicit_cast_impl<std::int64_t, To>(operand))
    {
        return implicit_cast_impl<std::int64_t, To>(operand);
    }
    else if (can_implicit_cast_impl<std::uint8_t, To>(operand))
    {
        return implicit_cast_impl<std::uint8_t, To>(operand);
    }
    else if (can_implicit_cast_impl<std::uint16_t, To>(operand))
    {
        return implicit_cast_impl<std::uint16_t, To>(operand);
    }
    else if (can_implicit_cast_impl<std::uint32_t, To>(operand))
    {
        return implicit_cast_impl<std::uint32_t, To>(operand);
    }
    else if (can_implicit_cast_impl<std::uint64_t, To>(operand))
    {
        return implicit_cast_impl<std::uint64_t, To>(operand);
    }
    else if (can_implicit_cast_impl<float, To>(operand))
    {
        return implicit_cast_impl<float, To>(operand);
    }
    else if (can_implicit_cast_impl<double, To>(operand))
    {
        return implicit_cast_impl<double, To>(operand);
    }
    else if (can_implicit_cast_impl<const char*, To>(operand))
    {
        return implicit_cast_impl<const char*, To>(operand);
    }
    else if (can_implicit_cast_impl<char, To>(operand))
    {
        return implicit_cast_impl<char, To>(operand);
    }
    else if (can_implicit_cast_impl<unsigned char, To>(operand))
    {
        return implicit_cast_impl<unsigned char, To>(operand);
    }
    else if (can_implicit_cast_impl<std::nullptr_t, To>(operand))
    {
        return implicit_cast_impl<std::nullptr_t, To>(operand);
    }

    throw "cannot implicit cast argument";
    To fallback{};
    return fallback;
}

template<typename T>
bool can_implicit_cast(const nonstd::any& operand)
{
    return detail::can_implicit_cast<T>(operand);
}
}
}

namespace egt
{

class AnyStream
{
public:
    using StorageType = std::vector<nonstd::any>;

    AnyStream()
    {
        m_buffer.reserve(8);
        m_bufferPtr = &m_buffer;
    }

    AnyStream(const StorageType& buff)
        : m_buffer()
        , m_bufferPtr(&buff)
    {
    }

    AnyStream(StorageType&& buff)
        : m_buffer(std::move(buff))
        , m_bufferPtr(&m_buffer)
    {
    }

    AnyStream(AnyStream&& rhs)
        : m_buffer(std::move(rhs.m_buffer))
        , m_bufferPtr(&m_buffer)
    {
        rhs.m_bufferPtr = nullptr;
    }
    
    
    AnyStream(AnyStream& rhs)
        : m_buffer(std::move(rhs.m_buffer))
        , m_bufferPtr(&m_buffer)
    {
        rhs.m_bufferPtr = nullptr;
    }
    
    AnyStream(const AnyStream& rhs)
        : m_buffer(rhs.m_buffer)
        , m_bufferPtr(&m_buffer)
    {
    }

    
    static AnyStream FromBuffer(std::vector<uint8_t>&&, bool)
    {
        throw("Cannot create AnyStream from raw buffer");
        return {};
    }

    std::vector<uint8_t> GetBuffer()
    {
        throw("Cannot return raw buffer from AnyStream");
        return {};
    }

    StorageType& GetStorage()
    {
        return m_buffer;
    }

    void Reset()
    {
        m_index = 0;
        m_buffer.clear();
        m_bufferPtr = &m_buffer;
        m_lastOperationResult = true;
    }

    template<typename T>
    AnyStream& Deserialize(T& t1)
    {
        if(false == m_lastOperationResult)
        {
            throw "invalid stream usage";
        }
        if(m_bufferPtr->empty())
        {
            m_lastOperationResult = false;
            return *this;
        }

        auto& anyVar = m_bufferPtr->at(m_index);

        t1 = nonstd::detail::implicit_cast<T>(anyVar);
        ++m_index;

        return *this;
    }

    template<typename T, typename ... Types>
    AnyStream& Deserialize(T& t1, Types& ...  args)
    {
        Deserialize(t1);
        Deserialize(args...);
        return *this;
    }

    AnyStream& Serialize()
    {
        return *this;
    }

    template<typename T>
    AnyStream& Serialize(T&& t1)
    {
        m_buffer.emplace_back(std::forward<T>(t1));
        return *this;
    }

    template<typename T, typename ... Types>
    AnyStream& Serialize(T&& t1, Types&& ...  args)
    {
        Serialize(std::forward<T>(t1));
        Serialize(std::forward<Types>(args)...);
        return *this;
    }

    template<typename T>
    AnyStream& operator<<(T&& var)
    {
        return Serialize(std::forward<T>(var));
    }

    template<typename T>
    AnyStream& operator>>(T& var)
    {
        return Deserialize(var);
    }

    explicit operator bool() const { return m_lastOperationResult; }

private:
    StorageType m_buffer;
    //used for deserialziation
    const StorageType* m_bufferPtr = nullptr;
    size_t m_index = 0;
    bool m_lastOperationResult = true;
};
}
#endif
