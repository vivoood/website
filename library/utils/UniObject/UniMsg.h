#ifndef __UniMsg_H
#define __UniMsg_H

#include <string>
#include <vector>

#include <UniStream.h>
#include <GenericMsg.h>

namespace egt
{
    using UniMsg = GenericMsg<oUniStream, iUniStream>;
}

#endif // __UniMsg_H
