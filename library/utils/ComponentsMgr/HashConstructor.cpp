#include "HashConstructor.h"
#include <stddef.h>

using namespace egt;

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(uint64_t typeHash, uint32_t x, uint32_t y, uint32_t d)
{
    char buff[8 + 4 + 4 + 4];

    int buffI = 0;

    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (typeHash >> (i * 8)) & 255ULL );
    }

    for (int i = 0; i < 4; i++)
    {
        buff[buffI++] = (char)( (x >> (i * 8)) & 255UL );
    }
    for (int i = 0; i < 4; i++)
    {
        buff[buffI++] = (char)( (y >> (i * 8)) & 255UL );
    }
    for (int i = 0; i < 4; i++)
    {
        buff[buffI++] = (char)( (d >> (i * 8)) & 255UL );
    }

    return crc64(buff, buffI);
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(uint64_t type_1_Hash, uint64_t type_2_Hash)
{
    char buff[8 + 8];

    int buffI = 0;

    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (type_1_Hash >> (i * 8)) & 255ULL );
    }
    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (type_2_Hash >> (i * 8)) & 255ULL );
    }

    return crc64(buff, buffI);
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(uint64_t typeHash, const char* fieldName, uint32_t fieldPos, bool isRequired)
{
    char buff[8 + 8 + 4 + 1];
    uint64_t nameHash = crc64(fieldName);

    int buffI = 0;
    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (typeHash >> (i * 8)) & 255ULL );
    }
    for (int i = 0; i < 8; i++)
    {
        buff[buffI++] = (char)( (nameHash >> (i * 8)) & 255ULL );
    }
    for (int i = 0; i < 4; i++)
    {
        buff[buffI++] = (char)( (fieldPos >> (i * 8)) & 255UL );
    }

    buff[buffI++] = isRequired ? 'T' : 'F';

    return crc64(buff, buffI);
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(const std::vector<uint64_t>& hashes)
{
    size_t sz = hashes.size() * sizeof(hashes[0]);
    uint64_t hash = crc64((char*)(&(hashes[0])), sz);
    return hash;
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::ConstructHash(const char* str)
{
    uint64_t hash = crc64(str);
    return hash;
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::crc64(const char *dataPtr, int sz)
{
    static bool                 tableReady = false;
    static unsigned long long   table[256];

    if (false == tableReady)
    {
        static unsigned long long   poly = 0xC96C5795D7870F42;
        tableReady = true;
        for(unsigned int i=0; i<256; ++i)
        {
            unsigned long long crc = i;
            for(int j=0; j<8; ++j)
            {
                if(crc & 1)
                {
                    crc >>= 1;
                    crc ^= poly;
                }
                else
                {
                    crc >>= 1;
                }
            }
            table[i] = crc;
        }
    }

    unsigned long long crc = 0;
    for(int i=0; i<sz; ++i)
    {
        unsigned char index = dataPtr[i] ^ crc;
        unsigned long long lookup = table[index];
        crc >>= 8;
        crc ^= lookup;
    }
    return crc;
}

///////////////////////////////////////////////////////////////////////////
uint64_t HashConstructor::crc64(const char *dataPtr)
{
    int sz = -1;
    while(dataPtr[++sz]);
    return crc64(dataPtr, sz);
}
