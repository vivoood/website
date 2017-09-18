#include <thread>
//
#include "PlatformThreads.h"

namespace Platform
{
namespace Threads
{
void ChangeName(std::thread& thread, const std::string &threadName)
{
    auto nameCopy = threadName;
    if(nameCopy.length() > 15)
    {
        nameCopy.resize(15);
    }
    auto handle = thread.native_handle();
    if (0 == handle)
    {
        return;
    }
    pthread_setname_np(handle, nameCopy.c_str());
}
}
}
