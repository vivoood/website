#ifndef __UniMsg_H
#define __UniMsg_H

#include <string>
#include <vector>

#include <lib_utils/UniStream/UniStream.h>
#include <lib_utils/GenericMsg/GenericMsg.h>

namespace egt
{
    using UniMsg = GenericMsg<oUniStream, iUniStream>;
}

#endif // __UniMsg_H
