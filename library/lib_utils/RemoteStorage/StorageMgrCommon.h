#ifndef __STORAGE_MGR_SERVICE_COMMON__
#define __STORAGE_MGR_SERVICE_COMMON__

#include <vector>
#include <string>
//#include <inttypes.h>

namespace egt
{
namespace RemoteStorage
{

struct WriteRequest
{
    std::string dataKey;
    size_t offset = 0;
    int gameId = 0;
    bool isGameParam = false;
    std::vector<uint8_t> data;
};

struct ReadRequest
{
    std::string dataKey;
    int gameId = 0;
    bool isGameParam = false;
};

struct ReadResult
{
    bool isOk = false;
    bool isSetupOnce = true;
    std::string dataKey;
    int gameId = 0;
    std::vector<uint8_t> data;
};

struct ParameterInfo
{
    bool isOk = false;
    bool isGameParam = false;
    bool isSetupOnce = true;
    int gameId = 0;
    size_t paramtereSize = 0;

};

}}

#endif // __STORAGE_MGR_SERVICE_COMMON__
