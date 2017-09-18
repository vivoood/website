#ifndef __VIRTUAL_STORAGE_H
#define __VIRTUAL_STORAGE_H
#include <string>
#include <vector>
#include <map>
#include <egt_lib/utils/Currency.h>
#include <limits>
#include <egt_lib/debug/egt_debug.h>

namespace egt{

enum class VS_SupportedTypes
{
    Type_char,
    Type_int8,
    Type_uint8,
    Type_int16,
    Type_uint16,
    Type_int32,
    Type_uint32,
    Type_int64,
    Type_uint64,
    Type_float,
    Type_double,
    Type_bool,
    Type_string,
    Type_currency,  // Currency
    Type_credits,   // Credits
    Type_percents,  // Percents
};

class VirtualStorage
{
public:
    class PartialSavePart
    {
    public:
        PartialSavePart();
        PartialSavePart(size_t offset, size_t size);
        size_t offset;
        size_t size;
    };

    struct StorageUnit
    {
        StorageUnit() : isArray(), maxArraySize(), storageOffset(), size(), targetType() {}
        std::string     type;
        std::string     name;
        bool            isArray;
        size_t          maxArraySize;
    private:
        size_t              storageOffset;
        size_t              size;
        VS_SupportedTypes   targetType;
        friend class VirtualStorage;
    };

    VirtualStorage();
    void Init(const std::vector<StorageUnit>& units);
    size_t GetStorageSize() const;

    bool IsChanged() const;
    const std::vector<u_int8_t>& GetBufferAndFlush(std::vector<PartialSavePart>& changedParts);
    void ApplyBuffer(const std::vector<u_int8_t>& buffer);

    template<typename ValueType>
    void SaveUnit(const std::string& unitName, const ValueType& value);
    template<typename ValueType>
    void SaveUnit(const std::string& unitName, const std::vector<ValueType>& value, size_t start = 0, size_t count = 0);

    void SaveUnit(const std::string& unitName, const std::string& value);
    void SaveUnit(const std::string& unitName, const std::vector<std::string>& value, size_t start = 0, size_t count = 0);
    void SaveUnit(const std::string& unitName, const char* value);

    void SaveUnit(const std::string& unitName, const Currency& value);
    void SaveUnit(const std::string& unitName, const std::vector<Currency>& value, size_t start = 0, size_t count = 0);
    void SaveUnit(const std::string& unitName, const Credits& value);
    void SaveUnit(const std::string& unitName, const std::vector<Credits>& value, size_t start = 0, size_t count = 0);
    void SaveUnit(const std::string& unitName, const Percents& value);
    void SaveUnit(const std::string& unitName, const std::vector<Percents>& value, size_t start = 0, size_t count = 0);

    /////////////////////////////////////////////////////////////////////////////////////
    template<typename ValueType>
    void LoadUnit(const std::string& unitName, ValueType& value) const;

    template<typename ValueType>
    void LoadUnit(const std::string& unitName, std::vector<ValueType>& value) const;

    //
    void LoadUnit(const std::string& unitName, std::string& value) const;
    void LoadUnit(const std::string& unitName, std::vector<std::string>& value) const;

    void LoadUnit(const std::string& unitName, Currency& value) const;
    void LoadUnit(const std::string& unitName, std::vector<Currency>& value) const;
    void LoadUnit(const std::string& unitName, Credits& value) const;
    void LoadUnit(const std::string& unitName, std::vector<Credits>& value) const;
    void LoadUnit(const std::string& unitName, Percents& value) const;
    void LoadUnit(const std::string& unitName, std::vector<Percents>& value) const;

private:
    template<typename ValueType>
    void _saveUnit(VS_SupportedTypes type, size_t offset, size_t size , const ValueType& value);

    template<typename ValueType>
    void _loadUnit(VS_SupportedTypes type, size_t offset, size_t size , ValueType& value) const;

    void _saveBaseValue(const void* valuePtr, size_t offset, size_t size);
    void _loadBaseValue(void* valuePtr, size_t offset, size_t size) const;
    void _markAsChanged(size_t offset);

    size_t GetUnitSize(const std::string& unitType) const;
    size_t GetUnitSize(const StorageUnit& unit) const;

    const std::map<std::string, VS_SupportedTypes>& GetStringToType() const;
    //
    std::map<std::string, StorageUnit> m_units;
    std::vector<u_int8_t> m_storage;
    bool m_isChanged;
    uint64_t m_changedMask;

};

#include "VirtualStorage.hpp"
} // egt

#endif // __VIRTUAL_STORAGE_H
