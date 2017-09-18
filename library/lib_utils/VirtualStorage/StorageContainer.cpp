#include "StorageContainer.h"

size_t LeadingZeroes(uint64_t& val)
{
    if (0ull == val){return 64;}
    if (val & 0x1ull){val >>= 1;return 0;}

    size_t c = 1;
    val >>= ((val & 0xffffffffull) == 0ull)?(c+=32, 32):0;
    val >>= ((val & 0xffffull) == 0ull)?(c+=16, 16):0;
    val >>= ((val & 0xff) == 0ull)?(c+=8, 8):0;
    val >>= ((val & 0xf) == 0ull)?(c+=4, 4):0;
    val >>= ((val & 0x3) == 0)?(c+=2, 2):0;
    uint8_t mask = val & 0x1ull;
    return (val >>= mask ? 1 : 2, c - mask);
}


///////////////////////////////////////////////////////////////////////////
StorageProfiler::StorageProfiler()
{

}

///////////////////////////////////////////////////////////////////////////
void StorageProfiler::Init(size_t storageSize)
{
    if (storageSize == 0)
    {
        return;
    }

    m_masks.clear();
    _init(storageSize);
}

///////////////////////////////////////////////////////////////////////////
void StorageProfiler::MarkChange(size_t offset)
{
    _markChange(offset, 0);
}

///////////////////////////////////////////////////////////////////////////
std::vector<size_t> StorageProfiler::GetChangesAndFlush()
{
    return _getChangesAndFlush(0);
}

///////////////////////////////////////////////////////////////////////////
void StorageProfiler::_init(size_t storageSize)
{
    size_t maskUnitsCount = ( storageSize + 63 ) / 64;
    m_masks.push_back(std::vector<uint64_t>());
    m_masks.back().resize(maskUnitsCount, 0ull);
    if (maskUnitsCount > 8)
    {
        _init(maskUnitsCount);
    }
}

///////////////////////////////////////////////////////////////////////////
void StorageProfiler::_markChange(size_t offset, size_t layer)
{
    size_t maskOffset = offset / 64;
    size_t bitOffset = offset % 64;
    m_masks[layer][maskOffset] |= (1ull << bitOffset);
    if (layer + 1 < m_masks.size())
    {
        _markChange(maskOffset, layer+1);
    }
}

///////////////////////////////////////////////////////////////////////////
std::vector<size_t> StorageProfiler::_getChangesAndFlush(size_t layer)
{
    std::vector<size_t> result;
    if (layer + 1 < m_masks.size())
    {
        auto changes = _getChangesAndFlush(layer + 1);
        for (size_t offs : changes)
        {
            uint64_t mask = m_masks[layer][offs];
            m_masks[layer][offs] = 0;
            size_t bitOffset = 0;
            while(mask)
            {
                bitOffset += LeadingZeroes(mask);
                result.push_back(offs * 64 + bitOffset);
                bitOffset++;
            }

        }
    }
    else
    {
        for (size_t offs = 0; offs < m_masks[layer].size(); offs++)
        {
            uint64_t mask = m_masks[layer][offs];
            m_masks[layer][offs] = 0;
            size_t bitOffset = 0;
            while(mask)
            {
                bitOffset += LeadingZeroes(mask);
                result.push_back(offs * 64 + bitOffset);
                bitOffset++;
            }
        }
    }
    return result;
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

#define STORAGE_CHUNK_SIZE (32) // bytes

///////////////////////////////////////////////////////////////////////////
StorageContainer::StorageContainer()
{

}

///////////////////////////////////////////////////////////////////////////
void StorageContainer::Init(const std::vector<uint8_t> &buff)
{
    m_storage = buff;
    m_profiler.Init( (buff.size() + STORAGE_CHUNK_SIZE - 1) / STORAGE_CHUNK_SIZE);
}

///////////////////////////////////////////////////////////////////////////
std::vector<StorageContainer::ChangedRegion> StorageContainer::GetChangesAndFlush()
{
    std::vector<StorageContainer::ChangedRegion> result;
    auto changes = m_profiler.GetChangesAndFlush();
    for(auto chunk : changes)
    {
        result.push_back( ChangedRegion(chunk * STORAGE_CHUNK_SIZE, STORAGE_CHUNK_SIZE) );
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
const std::vector<uint8_t> &StorageContainer::GetStorage() const
{
    return m_storage;
}

///////////////////////////////////////////////////////////////////////////
void StorageContainer::Write(std::size_t idx, uint8_t value)
{
    if (m_storage[idx] != value)
    {
        m_profiler.MarkChange( idx / STORAGE_CHUNK_SIZE );
        m_storage[idx] = value;
    }
}

///////////////////////////////////////////////////////////////////////////
uint8_t StorageContainer::Read(std::size_t idx) const
{
    return m_storage[idx];
}
