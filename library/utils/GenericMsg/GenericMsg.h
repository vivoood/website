#ifndef _GENERIC_MSG_H_
#define _GENERIC_MSG_H_

#include <string>
#include <vector>
#include <map>

namespace egt{
template<typename Serializer, typename Deserializer>
struct GenericMsgPrivateAccess;

template<typename Serializer, typename Deserializer>
struct GenericMsg
{
    //
    std::string             name; // "selec_view"

    // Deprecated. Please do not use.
    std::string             description;
    int64_t                 gameId;
    //
    //
    std::vector<std::string> GetValueNames() const;
    //
    template<typename T>
    void AddValue(const std::string& valueName, T&& value);
    //
    template<typename T>
    bool GetValue(const std::string& valueName, T& value) const;
    //
    bool HasValue(const std::string& valueName) const;
    //
    std::vector<uint8_t> Serialize() const;
    bool Deserialize( std::vector<uint8_t>&& buff );
    //
    friend struct GenericMsgPrivateAccess<Serializer, Deserializer>;
private:
    using ValueContainer = std::map<std::string, typename Serializer::StorageType>;
    ValueContainer m_values;
};

template<typename Serializer, typename Deserializer>
struct GenericMsgPrivateAccess
{
    using Msg = GenericMsg<Serializer, Deserializer>;
    static typename Msg::ValueContainer& GetValues(Msg& msg) { return msg.m_values; }
    static const typename Msg::ValueContainer& GetValues(const Msg& msg) { return msg.m_values; }
};

}

#include "GenericMsg.hpp"
#endif // _GENERIC_MSG_H_
