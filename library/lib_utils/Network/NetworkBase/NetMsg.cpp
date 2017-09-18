#include "NetMsg.h"
#include <string.h>


namespace egt
{

namespace NetMsgTools
{
template<typename T>
uint8_t* _writeIntToRaw(uint8_t* raw, T data)
{
    for (size_t i = 0; i < sizeof(T); i++)
    {
        raw[i] = (data >> (i * 8)) & 255;
    }
    return raw + sizeof(T);
}

template<typename T>
const uint8_t* _readIntFromRaw(const uint8_t* raw, T& data)
{
    data = 0;
    for (int i = sizeof (T) - 1; i >= 0; i--)
    {
        data <<= 8;
        data |= raw[i];
    }
    return raw + sizeof(T);
}
template<>
const uint8_t* _readIntFromRaw<uint8_t>(const uint8_t* raw, uint8_t& data)
{
    data = *raw;
    return raw + 1;
}
}

size_t NetMsg::GetMsgRawBufferSize() const
{
    return GetHeaderSize() + payload.size();
}

std::vector<uint8_t> NetMsg::Serialize(NetMsg&& msg)
{
    // serialize header
    PayloadSize payloadSize = msg.payload.size();
    HeaderSize headerSize = static_cast<HeaderSize>(GetHeaderSize());
    //
    std::vector<uint8_t> payload = std::move(msg.payload);
    payload.resize(payloadSize + headerSize);
    size_t copySz = headerSize;
    if (headerSize > payloadSize)
    {
        copySz = payloadSize;
    }
    for (size_t i = 0; i < copySz; i++)
    {
        payload[payloadSize + headerSize - copySz + i] = payload[i];
    }
    //
    uint8_t* ptr = payload.data();

    ptr = NetMsgTools::_writeIntToRaw(ptr, headerSize);
    ptr = NetMsgTools::_writeIntToRaw(ptr, payloadSize);
    ptr = NetMsgTools::_writeIntToRaw(ptr, msg.channel);
    ptr = NetMsgTools::_writeIntToRaw(ptr, msg.id);

    return payload;
}

std::vector<uint8_t> NetMsg::SerializeHeader(const NetMsg::Header &header)
{
    std::vector<uint8_t> raw(GetHeaderSize());
    // serialize header
    uint8_t* ptr = raw.data();
    HeaderSize headerSize = static_cast<HeaderSize>(GetHeaderSize());
    PayloadSize payloadSz = header.payloadSize;

    ptr = NetMsgTools::_writeIntToRaw(ptr, headerSize);
    ptr = NetMsgTools::_writeIntToRaw(ptr, payloadSz);
    ptr = NetMsgTools::_writeIntToRaw(ptr, header.channel);
    ptr = NetMsgTools::_writeIntToRaw(ptr, header.id);
    return raw;
}

egt::NetMsg NetMsg::Deserialize(std::vector<uint8_t>&& src)
{
    PayloadSize payloadSz;
    HeaderSize headerSize = static_cast<HeaderSize>(GetHeaderSize());

    if (GetHeaderSize() > src.size())
    {
        // TODO: assert
        return {};
    }

    NetMsg msg;
    msg.payload = std::move(src);
    const uint8_t* ptr = msg.payload.data();

    ptr = NetMsgTools::_readIntFromRaw(ptr, headerSize);
    ptr = NetMsgTools::_readIntFromRaw(ptr, payloadSz);
    ptr = NetMsgTools::_readIntFromRaw(ptr, msg.channel);
    ptr = NetMsgTools::_readIntFromRaw(ptr, msg.id);

    if (headerSize + payloadSz != msg.payload.size())
    {
        // TODO: assert
        return {};
    }

    size_t copySz = headerSize;
    if (headerSize > payloadSz)
    {
        copySz = payloadSz;
    }

    for (size_t i = 0; i < copySz; i++)
    {
        msg.payload[i] = msg.payload[payloadSz + headerSize - copySz + i];
    }

    msg.payload.resize(payloadSz);
    return msg;
}

NetMsg::Header NetMsg::DeserializeHeader(const uint8_t* src)
{
    Header header;
    const uint8_t* ptr = src;

    ptr = NetMsgTools::_readIntFromRaw(ptr, header.headerSize);
    ptr = NetMsgTools::_readIntFromRaw(ptr, header.payloadSize);
    ptr = NetMsgTools::_readIntFromRaw(ptr, header.channel);
    ptr = NetMsgTools::_readIntFromRaw(ptr, header.id);
    return  header;
}

}
