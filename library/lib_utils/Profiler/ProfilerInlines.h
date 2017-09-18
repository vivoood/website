#ifndef PROFILERINLINES_H
#define PROFILERINLINES_H
#include <cstdint>
#include <vector>
#include <time.h>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

namespace egt{
namespace ProfilerInlines {

inline int64_t TimespecDiffInMicro(const timespec& start, const timespec& stop)
{
    int64_t secDiff = stop.tv_sec - start.tv_sec;
    int64_t nSecDiff = stop.tv_nsec - start.tv_nsec;

    return (secDiff * 1000 * 1000) + (nSecDiff / 1000);
}

inline timespec TimespecDiff(const timespec& start, const timespec& stop)
{
    timespec result;
    if ((stop.tv_nsec - start.tv_nsec) < 0) {
        result.tv_sec = stop.tv_sec - start.tv_sec - 1;
        result.tv_nsec = stop.tv_nsec - start.tv_nsec + 1000000000;
    } else {
        result.tv_sec = stop.tv_sec - start.tv_sec;
        result.tv_nsec = stop.tv_nsec - start.tv_nsec;
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////
inline uint64_t GetMemoryUsage()
{
    FILE* file = fopen("/proc/self/stat", "r");
    char line[256];
    //read()
    fgets(line, 256, file);
    fclose(file);
    char* ptr = line;
    ptr = strchr (ptr, ')') + 2;

    for (int i = 0; i < 20; i++)
        ptr = strchr (ptr, ' ') + 1;

    unsigned long long mem = atoll(ptr);
    return mem;
}

///////////////////////////////////////////////////////////////////////////
inline int64_t GetMonotonicMicro()
{
    const auto steadyTime = std::chrono::high_resolution_clock::now();
    auto nowInMs = std::chrono::duration_cast<std::chrono::microseconds>(steadyTime.time_since_epoch()).count();
    return nowInMs;
}

///////////////////////////////////////////////////////////////////////////
inline int64_t GetMonotonicNano()
{
    const auto steadyTime = std::chrono::high_resolution_clock::now();
    auto nowInNs = std::chrono::duration_cast<std::chrono::nanoseconds>(steadyTime.time_since_epoch()).count();
    return nowInNs;
}

///////////////////////////////////////////////////////////////////////////
inline void GetThreadCpuTime(timespec& t)
{
    clock_gettime(CLOCK_THREAD_CPUTIME_ID,&t);
}

///////////////////////////////////////////////////////////////////////////
inline int64_t GetThreadCpuTime()
{
    timespec tSpec;
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tSpec);
    return static_cast<int64_t>(tSpec.tv_sec) * (1000 * 1000 * 1000) + tSpec.tv_nsec;
}

///////////////////////////////////////////////////////////////////////////
inline void GetProcessCpuTime(timespec& t)
{
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&t);
}

///////////////////////////////////////////////////////////////////////////
inline void Write8(std::vector<uint8_t> &container, uint8_t value)
{
    container.push_back(value);
}

///////////////////////////////////////////////////////////////////////////
inline size_t Read8(const std::vector<uint8_t> &container, size_t idx, uint8_t& value)
{
    value = container[idx];
    return idx + 1;
}

///////////////////////////////////////////////////////////////////////////
inline void Write16(std::vector<uint8_t> &container, uint16_t value)
{
    Write8(container, (value >> 0) & 255);
    Write8(container, (value >> 8) & 255);
}

///////////////////////////////////////////////////////////////////////////
inline size_t Read16(const std::vector<uint8_t> &container, size_t idx, uint16_t& value)
{
    uint16_t lsb = container[idx];
    uint16_t msb = container[idx+1];
    value = (msb << 8) | lsb;
    return idx + 2;
}

///////////////////////////////////////////////////////////////////////////
inline void Write32(std::vector<uint8_t> &container, uint32_t value)
{
    Write16(container, (value >> 0) & 65535);
    Write16(container, (value >> 16) & 65535);
}

///////////////////////////////////////////////////////////////////////////
inline size_t Read32(const std::vector<uint8_t> &container, size_t idx, uint32_t& value)
{
    uint16_t lsb16;
    uint16_t msb16;
    idx = Read16(container, idx, lsb16);
    idx = Read16(container, idx, msb16);
    uint32_t lsb = lsb16, msb = msb16;
    value = (msb << 16) | lsb;
    return idx;
}

///////////////////////////////////////////////////////////////////////////
inline void Write64(std::vector<uint8_t> &container, uint64_t value)
{
    Write32(container, (value >> 0) & ((1ull << 32) - 1));
    Write32(container, (value >> 32) & ((1ull << 32) - 1));
}

///////////////////////////////////////////////////////////////////////////
inline size_t Read64(const std::vector<uint8_t> &container, size_t idx, uint64_t& value)
{
    uint32_t lsb32;
    uint32_t msb32;
    idx = Read32(container, idx, lsb32);
    idx = Read32(container, idx, msb32);
    uint64_t lsb = lsb32, msb = msb32;
    value = (msb << 32) | lsb;
    return idx;
}
}
}

#endif // PROFILERINLINES_H
