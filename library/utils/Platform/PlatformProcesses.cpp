#include "PlatformProcesses.h"
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <sstream>
#include <regex>
#include <map>

namespace Platform
{
namespace Processes
{

std::string GetPidByName(const std::string& processName)
{
    int pid = -1;

    // Open the /proc directory
    DIR *dp = opendir("/proc");
    if (dp != NULL)
    {
        // Enumerate all entries in directory until process found
        struct dirent *dirp;
        while (pid < 0 && (dirp = readdir(dp)))
        {
            // Skip non-numeric entries
            int id = atoi(dirp->d_name);
            if (id > 0)
            {
                // Read contents of virtual /proc/{pid}/cmdline file
                std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
                std::ifstream cmdFile(cmdPath.c_str());
                std::string cmdLine;
                std::getline(cmdFile, cmdLine);
                if (!cmdLine.empty())
                {
                    // Keep first cmdline item which contains the program path
                    size_t pos = cmdLine.find('\0');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(0, pos);
                    // Keep program name only, removing the path
                    pos = cmdLine.rfind('/');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(pos + 1);
                    // Compare against requested process name
                    if (processName == cmdLine)
                    {
                        pid = id;
                        break;
                    }
                }
            }
        }
    }

    std::string strPID = std::to_string(pid);
    return strPID;
}

namespace Memory
{

const char* const cMeminfoFile = "/proc/meminfo";

struct assocMemoryMultiplier
{
    const char* str;
    uint64_t value;
};

static const assocMemoryMultiplier units_map[] =
{
    { "kB", 1_KB },
    { "mB", 1_MB },
    { "gB", 1_GB }
};

enum class MemoryInfoFields
{
    TotalMemory,
    AvailableMemory,
};

static std::map<MemoryInfoFields, const std::regex> s_procMemInfoFields =
{
    { MemoryInfoFields::TotalMemory, std::regex("^MemTotal:\\s+(\\d+)\\s?(kB|mB|gB)$") },
    { MemoryInfoFields::AvailableMemory, std::regex("^MemAvailable:\\s+(\\d+)\\s?(kB|mB|gB)$") }
};

uint64_t GetProcessMemoryUsage(pid_t pid)
{
    std::stringstream ss;
    ss << "/proc/";
    ss << pid;
    ss << "/status";
    auto str = ss.str();

    std::ifstream meminfo( ss.str(), std::ifstream::in );

    if( !meminfo.is_open() )
    {
        throw std::runtime_error("Unable to open status file.");
    }

    static const std::regex MemRegex("^VmRSS:\\s+(\\d+)\\s?(kB|mB|gB)$");

    std::string line;
    std::smatch lineMatch;

    uint64_t usedMemory = 0;

    while( std::getline( meminfo, line ) )
    {
        if( std::regex_search( line, lineMatch, MemRegex ) )
        {
            auto value = lineMatch[1].str();
            auto units = lineMatch[2].str();

            usedMemory = std::stoul( value );

            // Don't check if index is valid, because units are checked by regex and they match one of units_map values
            auto index = std::find_if( std::begin( units_map ), std::end( units_map ), [&units]( const assocMemoryMultiplier& m ) { return ( units == m.str ); } );

            usedMemory *= index->value;

            break;
        }
    }

    return usedMemory;
}

// Get field from /proc/meminfo
uint64_t GetMemoryInfoField(MemoryInfoFields memoryField)
{
    std::ifstream meminfo( cMeminfoFile, std::ifstream::in );

    if( !meminfo.is_open() )
    {
        throw std::runtime_error("Unable to open /proc/meminfo.");
    }

    uint64_t memField = 0;

    auto memInfo = s_procMemInfoFields.find(memoryField);
    if(memInfo == s_procMemInfoFields.end())
    {
        return memField;
    }
    const std::regex& MemRegex = memInfo->second;

    std::string line;
    std::smatch lineMatch;

    while( std::getline( meminfo, line ) )
    {
        if( std::regex_search( line, lineMatch, MemRegex ) )
        {
            // Available memory: line found
            auto value = lineMatch[1].str();
            auto units = lineMatch[2].str();

            memField = std::stoul( value );

            // Don't check if index is valid, because units are checked by regex and they match one of units_map values
            auto index = std::find_if( std::begin( units_map ), std::end( units_map ), [&units]( const assocMemoryMultiplier& m ) { return ( units == m.str ); } );

            memField *= index->value;

            break;
        }
    }

    return memField;
}

uint64_t GetAvailableMemory()
{
    return GetMemoryInfoField(MemoryInfoFields::AvailableMemory);
}

uint64_t GetTotalMemory()
{
    return GetMemoryInfoField(MemoryInfoFields::TotalMemory);
}

} // Memory
} // Processes
} // Platform
