#ifndef NETMSG_H
#define NETMSG_H
#include "cstddef"
#include <cinttypes>
#include <vector>

namespace egt
{

class NetMsg
{
public:
    using Channel = uint64_t;
    using PayloadSize = uint32_t;
    using HeaderSize = uint8_t;
    using Id = uint16_t;
    struct Header
    {
        HeaderSize headerSize = 0;
        PayloadSize payloadSize = 0;
        //
        Channel channel = 0;
        Id id = 0;
    };

    Channel channel = 0;
    Id id = 0;
    std::vector<uint8_t> payload;

    static constexpr size_t GetHeaderSize()
    {
        return sizeof(HeaderSize) + sizeof(PayloadSize) + sizeof(Channel) + sizeof(Id);
    }
    size_t GetMsgRawBufferSize() const;
    static std::vector<uint8_t> Serialize(NetMsg&& msg);
    static std::vector<uint8_t> SerializeHeader(const Header& header);
    static NetMsg Deserialize(std::vector<uint8_t>&& src); // returns systemId
    static Header DeserializeHeader(const uint8_t* src);
};
}
#endif // NETMSG_H
