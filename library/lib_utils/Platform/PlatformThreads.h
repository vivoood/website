#ifndef _EGT_PLATFORM_THREADS_H
#define _EGT_PLATFORM_THREADS_H
#include <string>
namespace std
{
    class thread;
}

namespace Platform
{
namespace Threads
{
void ChangeName(std::thread& thread, const std::string &threadName);
}
}

#endif // _EGT_PLATFORM_THREADS_H
