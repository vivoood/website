#ifndef __EGT_PROFILER_MGR_INTERFACE_H__
#define __EGT_PROFILER_MGR_INTERFACE_H__
#include <cstdint>
#include <vector>

namespace egt
{
namespace ProfilerInterface
{

enum MsgId : uint32_t
{
    StartProfiling,
    EndProfiling,
    ProfilingData,
    GL_DataRequest,
    GL_Data,
    GL_StartCustomProfiling,
    GL_StopCustomProfiling,
    GL_CustomProfilingData
};

struct Config
{
    uint32_t maxTimeMs = 5000;
    uint32_t cpuProfilingDepth = 32;
    uint32_t memProfilingDepth = 4;

    std::vector<uint8_t> ToRaw()
    {
        std::vector<uint8_t> raw(s_size);
        auto ptr = raw.data();
        ptr = _writeIntToRaw(ptr, maxTimeMs);
        ptr = _writeIntToRaw(ptr, cpuProfilingDepth);
        ptr = _writeIntToRaw(ptr, memProfilingDepth);
        return raw;
    }

    void FromRaw(const std::vector<uint8_t>& raw)
    {
        if (s_size > raw.size())
        {
            maxTimeMs = cpuProfilingDepth = memProfilingDepth = 0;
            return;
        }
        auto ptr = raw.data();
        ptr = _readIntFromRaw(ptr, maxTimeMs);
        ptr = _readIntFromRaw(ptr, cpuProfilingDepth);
        ptr = _readIntFromRaw(ptr, memProfilingDepth);
    }

private:
    static constexpr auto s_size = (sizeof (maxTimeMs) + sizeof (cpuProfilingDepth) + sizeof (memProfilingDepth));
    template<typename T>
    uint8_t* _writeIntToRaw(uint8_t* raw, T data)
    {
        for (unsigned i = 0; i < sizeof(T); i++)
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
};
}
}



#endif // __EGT_PROFILER_MGR_INTERFACE_H__
