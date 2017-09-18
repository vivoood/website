#ifndef UNISTR_UNI_STREAM_H
#define UNISTR_UNI_STREAM_H

#include "UniSerializer.h"
#include "UniDeserializer.h"


/*
    (0)         is known type   (0 = unknown, 1 = known)
    (1)         is integral type(0 = non int, 1 = int)
    (2, 3)      type size       (0 = 1, 1 = 2, 2 = 4, 3 = 8) or (1 << n times)
    (4)         is signed       (0 = unsigned, 1 = signed)
    (5)         is array type   (0 = not array, 1 = array)
*/




/*====================================================
*
*   Stream buffer description
*   
*   Everything is in little endian format.
*   
*   Stream buffer format:
*   
*   Header (#headerSize = 4)
*   4 bytes (#bufferSize) - size of buffer including stream header
*   --------
*   Payload (#payloadSize = #bufferSize - 4):
*   1 byte (#itemType) item type
*====================================================*/

namespace egt
{
    using UniSerializer = oUniStream;
    using oUniInplace = oUniStream::Inplace;
    using UniDeserializer = iUniStream;
    using iUniInplace = UniDeserializer::Inplace;
}

#endif // UNISTR_UNI_STREAM_H
