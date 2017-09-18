#ifndef STORAGEVOLUME_H
#define STORAGEVOLUME_H

#include "StorageContainer.h"
#include <vector>
#include <string>



class StorageVolume
{
public:
    struct VolumeHeader
    {
        VolumeHeader();
        VolumeHeader(const StorageContainer& container);
        void Save(StorageContainer& container) const;
        bool        isFormated;
        uint64_t    volumeStructureHash;
        int64_t     lastWriteAccessTime;
        uint16_t    parametersCount;
        uint16_t    freeSectorsList;
        uint8_t     parametersEntyPointOffset;
    };

    struct Parameter
    {
        std::string name;
        size_t      parameterId;
        std::string storageName;
        friend class StorageVolume;
    };
    StorageVolume();
    void UploadStorage(const std::vector<uint8_t>& buff);
    bool Init(std::vector<StorageVolume::Parameter*>& parameters, const std::vector<uint8_t>& buff);
    void Format(std::vector<StorageVolume::Parameter*>& parameters, size_t storageSize, int64_t now);
    bool IsParameterSet(size_t parameterId) const;
    void ReadParameter(size_t parameterId, std::vector<uint8_t>& out) const;
    void SaveParameter(size_t parameterId, const std::vector<uint8_t>& in, int64_t now);
    void UnsetParameter(size_t parameterId, int64_t now);
    size_t GetFreeSectorsCount() const;
    std::vector<StorageContainer::ChangedRegion> GetChangesAndFlush();
    const std::vector<uint8_t> &GetStorage() const;
    VolumeHeader Header() const;

private:

    template<size_t SECTOR_SZ, size_t START_OFFS>
    struct SectorHeader
    {
        SectorHeader(uint16_t sectorNumber);
        SectorHeader(const StorageContainer& container, uint16_t sectorNumber);

        void Save(StorageContainer& container,
                  const std::vector<uint8_t>& buff,
                  size_t& start,
                  size_t& sz,
                  uint16_t nextSector);

        static size_t Size() { return SECTOR_SZ; };
        size_t CalcSectorCapacity( size_t dataSize ) const;
        //
        uint8_t     sectorPayloadSize;
        bool        hasNextSector;
        bool        isSet;
        size_t      sectorPayloadStart;
        uint16_t    nextParameterSector;
        uint16_t    sectorNumber;
    };
    typedef SectorHeader<32, 0> NormalSector;
    typedef SectorHeader<16, 0> EntrySector;


    uint64_t CalcHash(std::vector<StorageVolume::Parameter*>& parameters);
    void InitParametersList(std::vector<StorageVolume::Parameter*>& parameters);
    uint16_t GetFreeSector();
    void FreeSectorChain(uint16_t sectorNum);
    void FreeSector(uint16_t sectorNum);
    StorageContainer m_container;
};

#endif // STORAGEVOLUME_H
