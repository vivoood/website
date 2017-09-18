#ifndef STORAGECONTAINER_H
#define STORAGECONTAINER_H

#include <stdint.h>
#include <vector>

#include <stddef.h>

class StorageProfiler
{
public:
    StorageProfiler();
    void Init(size_t storageSize);
    void MarkChange(size_t offset);
    std::vector<size_t> GetChangesAndFlush();
private:
    void _init(size_t storageSize);
    void _markChange(size_t offset, size_t layer);
    std::vector<size_t> _getChangesAndFlush(size_t layer);

    std::vector<std::vector<uint64_t>> m_masks;
    std::vector<size_t> m_chunksCount;
};

class StorageContainer
{
public:
    struct ChangedRegion
    {
        ChangedRegion() : offset(0), size(0){};
        ChangedRegion(size_t o, size_t s) : offset(o), size(s){};
        size_t offset;
        size_t size;
    };

    StorageContainer();
    void Init( const std::vector<uint8_t>& buff );
    std::vector<ChangedRegion> GetChangesAndFlush();
    const std::vector<uint8_t> &GetStorage() const;

    void Write(std::size_t idx, uint8_t value);
    uint8_t Read(std::size_t idx) const;
    size_t Size() const {return m_storage.size();};
private:

    std::vector<uint8_t>    m_storage;
    StorageProfiler         m_profiler;
};

#endif // STORAGECONTAINER_H
