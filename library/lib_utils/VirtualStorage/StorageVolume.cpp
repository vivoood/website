#include "StorageVolume.h"
#include <assert.h>
#include "../Crc.h"

#define ZERO_ENTRY_SECTOR (4)

///////////////////////////////////////////////////////////////////////////
size_t Write8(StorageContainer &container, size_t idx, uint8_t value)
{
    container.Write(idx, value);
    return idx + 1;
}

///////////////////////////////////////////////////////////////////////////
size_t Read8(const StorageContainer &container, size_t idx, uint8_t& value)
{
    value = container.Read(idx);
    return idx + 1;
}

///////////////////////////////////////////////////////////////////////////
size_t Write16(StorageContainer &container, size_t idx, uint16_t value)
{
    container.Write( idx, (value >> 0) & 255);
    container.Write( idx+1, (value >> 8) & 255);
    return idx + 2;
}

///////////////////////////////////////////////////////////////////////////
size_t Read16(const StorageContainer &container, size_t idx, uint16_t& value)
{
    uint16_t lsb = container.Read(idx);
    uint16_t msb = container.Read(idx+1);
    value = (msb << 8) | lsb;
    return idx + 2;
}

///////////////////////////////////////////////////////////////////////////
size_t Write32(StorageContainer &container, size_t idx, uint32_t value)
{
    idx = Write16(container, idx, (value >> 0) & 65535);
    idx = Write16(container, idx, (value >> 16) & 65535);
    return idx;
}

///////////////////////////////////////////////////////////////////////////
size_t Read32(const StorageContainer &container, size_t idx, uint32_t& value)
{
    uint16_t lsb16;
    uint16_t msb16;
    idx = Read16(container, idx, lsb16);
    idx = Read16(container, idx, msb16);
    uint32_t lsb = lsb16, msb = msb16;
    value = (msb << 16) | lsb;
    return idx;
}

///////////////////////////////////////////////////////////////////////////
size_t Write64(StorageContainer &container, size_t idx, uint64_t value)
{
    idx = Write32(container, idx, (value >> 0) & ((1ull << 32) - 1));
    idx = Write32(container, idx, (value >> 32) & ((1ull << 32) - 1));
    return idx;
}

///////////////////////////////////////////////////////////////////////////
size_t Read64(const StorageContainer &container, size_t idx, uint64_t& value)
{
    uint32_t lsb32;
    uint32_t msb32;
    idx = Read32(container, idx, lsb32);
    idx = Read32(container, idx, msb32);
    uint64_t lsb = lsb32, msb = msb32;
    value = (msb << 32) | lsb;
    return idx;
}

///////////////////////////////////////////////////////////////////////////
StorageVolume::VolumeHeader::VolumeHeader()
    : isFormated(false)
    , volumeStructureHash(0)
    , lastWriteAccessTime(0)
    , parametersCount(0)
    , freeSectorsList(0)
    , parametersEntyPointOffset(0)
{}

///////////////////////////////////////////////////////////////////////////
StorageVolume::VolumeHeader::VolumeHeader(const StorageContainer &container)
{
    size_t idx = 0;
    uint8_t isFormatedInt8;
    uint64_t lastMod = 0;
    idx = Read8(container, idx, isFormatedInt8); isFormated = (isFormatedInt8 == 'Y');
    idx = Read64(container, idx, volumeStructureHash);
    idx = Read64(container, idx, lastMod); lastWriteAccessTime = (int64_t)lastMod;
    idx = Read16(container, idx, parametersCount);
    idx = Read16(container, idx, freeSectorsList);
    idx = Read8(container, idx, parametersEntyPointOffset);
}

///////////////////////////////////////////////////////////////////////////
void StorageVolume::VolumeHeader::Save(StorageContainer &container) const
{
    size_t idx = 0;
    idx = Write8(container, idx, isFormated ? 'Y' : 0);
    idx = Write64(container, idx, volumeStructureHash);
    idx = Write64(container, idx, lastWriteAccessTime);
    idx = Write16(container, idx, parametersCount);
    idx = Write16(container, idx, freeSectorsList);
    idx = Write8(container, idx, parametersEntyPointOffset);
}

///////////////////////////////////////////////////////////////////////////
template<size_t SECTOR_SZ, size_t START_OFFS>
StorageVolume::SectorHeader<SECTOR_SZ, START_OFFS>::SectorHeader(uint16_t sectorNumber)
    : sectorPayloadSize(0)
    , hasNextSector(false)
    , isSet(false)
    , sectorPayloadStart(0)
    , nextParameterSector(0)
    , sectorNumber(sectorNumber)
{}

///////////////////////////////////////////////////////////////////////////
template<size_t SECTOR_SZ, size_t START_OFFS>
StorageVolume::SectorHeader<SECTOR_SZ, START_OFFS>::SectorHeader
(const StorageContainer &container, uint16_t sectorNumber)
    : sectorNumber(sectorNumber)
{
    size_t sectorOffset = sectorNumber;
    sectorOffset *= SECTOR_SZ;
    sectorOffset += START_OFFS;
    size_t idx = sectorOffset;
    idx = Read8(container, idx, sectorPayloadSize);
    uint8_t flags = sectorPayloadSize >> 5;
    sectorPayloadSize &= ((1 << 5) - 1);
    if (flags & 1)
    {
        hasNextSector = true;
        sectorPayloadStart = sectorOffset + 3;
        idx = Read16(container, idx, nextParameterSector);
    }
    else
    {
        hasNextSector = false;
        sectorPayloadStart = sectorOffset + 1;
        nextParameterSector = 0;
    }
    isSet = (flags & 2) != 0;
}

///////////////////////////////////////////////////////////////////////////
template<size_t SECTOR_SZ, size_t START_OFFS>
void StorageVolume::SectorHeader<SECTOR_SZ, START_OFFS>::Save(  StorageContainer& container,
                                                                const std::vector<uint8_t>& buff,
                                                                size_t& start,
                                                                size_t& sz,
                                                                uint16_t nextSector)
{
    size_t sectorOffset = sectorNumber;
    sectorOffset *= SECTOR_SZ;
    sectorOffset += START_OFFS;
    size_t idx = sectorOffset;
    size_t max = CalcSectorCapacity(sz);
    hasNextSector = nextSector != 0;
    if (max >= sz)
    {
        sectorPayloadSize = sz;
        sectorPayloadStart = sectorOffset + 1;
    }
    else
    {
        sectorPayloadSize = (uint8_t)max;
        sectorPayloadStart = sectorOffset + 3;
    }
    nextParameterSector = nextSector;

    uint8_t mask = hasNextSector ? 1 : 0;
    mask |= isSet?2:0;
    mask <<= 5;
    idx = Write8(container, idx, sectorPayloadSize | mask);
    if (hasNextSector)
    {
        idx = Write16(container, idx, nextParameterSector);
    }
    for (size_t i = 0; i < sectorPayloadSize; i++)
    {
        Write8(container, sectorPayloadStart + i, buff[start + i]);
    }
    start += sectorPayloadSize;
    sz -= sectorPayloadSize;
}

///////////////////////////////////////////////////////////////////////////
template<size_t SECTOR_SZ, size_t START_OFFS>
size_t StorageVolume::SectorHeader<SECTOR_SZ, START_OFFS>::CalcSectorCapacity(size_t dataSize) const
{
    if (dataSize <= SECTOR_SZ - 1)
    {
        return dataSize;
    }
    return SECTOR_SZ - 3;
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
StorageVolume::StorageVolume()
{

}

///////////////////////////////////////////////////////////////////////////
void StorageVolume::UploadStorage(const std::vector<uint8_t> &buff)
{
    m_container.Init(buff);
}

///////////////////////////////////////////////////////////////////////////
bool StorageVolume::Init(std::vector<StorageVolume::Parameter*>& parameters, const std::vector<uint8_t> &buff)
{
    uint64_t hashCheck = CalcHash(parameters);

    m_container.Init(buff);
    InitParametersList(parameters);

    if (VolumeHeader(m_container).volumeStructureHash != hashCheck)
    {
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
void StorageVolume::Format(std::vector<StorageVolume::Parameter*> &parameters, size_t storageSize, int64_t now)
{
    m_container.Init(std::vector<uint8_t>(storageSize, 0));
    VolumeHeader volumeHeader;
    volumeHeader.isFormated = true;
    volumeHeader.volumeStructureHash = CalcHash(parameters);
    volumeHeader.lastWriteAccessTime = now;
    volumeHeader.parametersCount = (uint16_t)parameters.size();
    volumeHeader.parametersEntyPointOffset = ZERO_ENTRY_SECTOR * EntrySector::Size();
    size_t entryPointEnd = volumeHeader.parametersEntyPointOffset + volumeHeader.parametersCount * EntrySector::Size();
    volumeHeader.freeSectorsList = entryPointEnd / NormalSector::Size() + 1;
    volumeHeader.Save(m_container);

    size_t zero = 0;
    size_t maxSectors = m_container.Size() / NormalSector::Size() - 8;
    for (uint16_t freeSectorNum = volumeHeader.freeSectorsList; freeSectorNum < maxSectors; freeSectorNum++)
    {
        NormalSector sector(freeSectorNum);
        if (freeSectorNum < maxSectors - 1)
        {
            sector.Save(m_container, {}, zero, zero, freeSectorNum + 1);
        }
        else
        {
            sector.Save(m_container, {}, zero, zero, 0);
        }
    }

    InitParametersList(parameters);
    for (auto param : parameters)
    {
        EntrySector sector(static_cast<uint16_t>(param->parameterId));
        sector.isSet = false;
        sector.Save(m_container, {}, zero, zero, 0);
    }
}

///////////////////////////////////////////////////////////////////////////
bool StorageVolume::IsParameterSet(size_t parameterId) const
{
    return EntrySector(m_container, parameterId).isSet;
}

///////////////////////////////////////////////////////////////////////////
void StorageVolume::ReadParameter(size_t parameterId, std::vector<uint8_t> &out) const
{
    out.clear();
    EntrySector entrySector(m_container, parameterId);
    size_t from = entrySector.sectorPayloadStart;
    for (size_t i = 0; i < entrySector.sectorPayloadSize; i++)
    {
        uint8_t v;
        from = Read8(m_container, from, v);
        out.push_back( v );
    }

    if (false == entrySector.hasNextSector)
    {
        return;
    }
    uint16_t nextSector = entrySector.nextParameterSector;
    while(nextSector != 0)
    {
        NormalSector sector(m_container, nextSector);
        size_t from = sector.sectorPayloadStart;
        for (size_t i = 0; i < sector.sectorPayloadSize; i++)
        {
            uint8_t v;
            from = Read8(m_container, from, v);
            out.push_back( v );
        }
        nextSector = (sector.hasNextSector) ? sector.nextParameterSector : 0;
    }
}

///////////////////////////////////////////////////////////////////////////
void StorageVolume::SaveParameter(size_t parameterId, const std::vector<uint8_t> &in, int64_t now)
{
    EntrySector entrySector(m_container, (uint16_t)parameterId);
    entrySector.isSet = true;
    uint16_t nextSector = entrySector.hasNextSector ? entrySector.nextParameterSector : 0;

    size_t start = 0;
    size_t sz = in.size();
    bool isNextSectorFree = false;
    if (entrySector.CalcSectorCapacity(sz) < sz)
    {
        if (0 == nextSector)
        {
            nextSector = GetFreeSector();
            isNextSectorFree = true;
        }
        entrySector.Save(m_container, in, start, sz, nextSector);
    }
    else
    {
        entrySector.Save(m_container, in, start, sz, 0);
    }

    while(sz)
    {
        NormalSector sector(m_container, nextSector);
        if (isNextSectorFree)
        {
            nextSector = 0;
        }
        else
        {
            nextSector = sector.hasNextSector ? sector.nextParameterSector : 0;
        }
        if (sector.CalcSectorCapacity(sz) < sz)
        {
            if (0 == nextSector)
            {
                nextSector = GetFreeSector();
                isNextSectorFree = true;
            }
            sector.Save(m_container, in, start, sz, nextSector);
        }
        else
        {
            sector.Save(m_container, in, start, sz, 0);
        }
    }
    FreeSectorChain(nextSector);
    VolumeHeader volumeHeader(m_container);
    volumeHeader.lastWriteAccessTime = now;
    volumeHeader.Save(m_container);
}

///////////////////////////////////////////////////////////////////////////
void StorageVolume::UnsetParameter(size_t parameterId, int64_t now)
{
    EntrySector entrySector(m_container, (uint16_t)parameterId);
    uint16_t nextSector = entrySector.hasNextSector ? entrySector.nextParameterSector : 0;
    FreeSectorChain(nextSector);
    size_t zero = 0;
    entrySector.isSet = false;
    entrySector.Save(m_container, {}, zero, zero, 0);
    VolumeHeader volumeHeader(m_container);
    volumeHeader.lastWriteAccessTime = now;
    volumeHeader.Save(m_container);
}

///////////////////////////////////////////////////////////////////////////
size_t StorageVolume::GetFreeSectorsCount() const
{
    VolumeHeader volumeHeader(m_container);
    uint16_t freeSecotrId = volumeHeader.freeSectorsList;
    size_t result = 0;
    while(freeSecotrId != 0)
    {
        result++;
        freeSecotrId = NormalSector(m_container, freeSecotrId).nextParameterSector;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
std::vector<StorageContainer::ChangedRegion> StorageVolume::GetChangesAndFlush()
{
    return m_container.GetChangesAndFlush();
}

///////////////////////////////////////////////////////////////////////////
const std::vector<uint8_t> &StorageVolume::GetStorage() const
{
    return m_container.GetStorage();
}

///////////////////////////////////////////////////////////////////////////
uint64_t StorageVolume::CalcHash(std::vector<StorageVolume::Parameter *> &parameters)
{
    uint64_t hash = 0xC0CAC01A;
    for (auto param : parameters)
    {
        CRC::hash_combine(hash, param->name);
    }
    return hash;
}

///////////////////////////////////////////////////////////////////////////
void StorageVolume::InitParametersList(std::vector<StorageVolume::Parameter *> &parameters)
{
    for(size_t paramNumber = 0; paramNumber < parameters.size(); paramNumber++)
    {
        size_t entrySectorNum = ZERO_ENTRY_SECTOR + paramNumber;
        parameters[paramNumber]->parameterId = entrySectorNum;
    }
}

///////////////////////////////////////////////////////////////////////////
uint16_t StorageVolume::GetFreeSector()
{
    VolumeHeader volumeHeader(m_container);
    uint16_t firstFree = volumeHeader.freeSectorsList;
    if (0 == firstFree)
    {
        assert("Storage is FULL !");
        return 0;
    }
    NormalSector sector(m_container, firstFree);
    volumeHeader.freeSectorsList = sector.nextParameterSector;
    volumeHeader.Save(m_container);
    return firstFree;
}

void StorageVolume::FreeSectorChain(uint16_t sectorNum)
{
    while(sectorNum)
    {
        NormalSector sector(m_container, sectorNum);
        sectorNum = sector.hasNextSector ? sector.nextParameterSector : 0;
        FreeSector(sector.sectorNumber);
    }
}

///////////////////////////////////////////////////////////////////////////
void StorageVolume::FreeSector(uint16_t sectorNum)
{
    VolumeHeader volumeHeader(m_container);
    NormalSector sector(m_container, sectorNum);
    size_t zero = 0;
    sector.Save(m_container, {}, zero, zero, volumeHeader.freeSectorsList);
    volumeHeader.freeSectorsList = sectorNum;
    volumeHeader.Save(m_container);
}

StorageVolume::VolumeHeader StorageVolume::Header() const
{
    return VolumeHeader(m_container);
}
