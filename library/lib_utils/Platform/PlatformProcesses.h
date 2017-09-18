#ifndef EGT_PLATFORM_PROCESSES_H
#define EGT_PLATFORM_PROCESSES_H

#include <string>

namespace Platform
{
namespace Processes
{
    std::string GetPidByName(const std::string& processName);
}
}

// Memory related functionality
namespace Platform
{
namespace Processes
{
namespace Memory
{
    constexpr uint64_t operator"" _KB ( unsigned long long int val )
    {
        return val * 1024;
    }

    constexpr uint64_t operator"" _MB ( unsigned long long int val )
    {
        return val * 1024 * 1024;
    }

    constexpr uint64_t operator"" _GB ( unsigned long long int val )
    {
        return val * 1024 * 1024 * 1024;
    }

    uint64_t GetProcessMemoryUsage(pid_t pid);
    uint64_t GetAvailableMemory();
    uint64_t GetTotalMemory();

} // Memory
} // Processes
} // Platform

#endif // EGT_PLATFORM_PROCESSES_H
