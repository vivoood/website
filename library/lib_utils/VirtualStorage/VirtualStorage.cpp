#include "VirtualStorage.h"
#include <map>
#include <egt_lib/debug/egt_debug.h>

using namespace egt;

int LeadingZeroes2(uint64_t& val)
{
    if (0ull == val)
    {
        return 64;
    }
    if (val & 0x1ull)
    {
        val >>= 1;
        return 0;
    }

    int c = 1;
    if ((val & 0xffffffffull) == 0ull)
    {
        val >>= 32;
        c += 32;
    }
    if ((val & 0xffffull) == 0ull)
    {
        val >>= 16;
        c += 16;
    }
    if ((val & 0xff) == 0ull)
    {
        val >>= 8;
        c += 8;
    }
    if ((val & 0xf) == 0ull)
    {
        val >>= 4;
        c += 4;
    }
    if ((val & 0x3) == 0)
    {
        val >>= 2;
        c += 2;
    }
    uint8_t mask = val & 0x1ull;
    val >>= mask ? 1 : 2;
    c -= mask;
    return c;
}



static std::map<std::string, VS_SupportedTypes> stringToType =
{
      {"char",          VS_SupportedTypes::Type_char},
      {"int8",          VS_SupportedTypes::Type_int8},
      {"uint8",         VS_SupportedTypes::Type_uint8},
      {"int16",         VS_SupportedTypes::Type_int16},
      {"uint16",        VS_SupportedTypes::Type_uint16},
      {"int32",         VS_SupportedTypes::Type_int32},
      {"uint32",        VS_SupportedTypes::Type_uint32},
      {"int64",         VS_SupportedTypes::Type_int64},
      {"uint64",        VS_SupportedTypes::Type_uint64},
      {"float",         VS_SupportedTypes::Type_float},
      {"double",        VS_SupportedTypes::Type_double},
      {"bool",          VS_SupportedTypes::Type_bool},
      {"string",        VS_SupportedTypes::Type_string},
      {"currency",      VS_SupportedTypes::Type_currency},
      {"credits",       VS_SupportedTypes::Type_credits},
      {"percents",      VS_SupportedTypes::Type_percents},
};

//////////////////////////////////////////////////////////
VirtualStorage::PartialSavePart::PartialSavePart()
    : offset(0)
    , size(0)
{}

//////////////////////////////////////////////////////////
VirtualStorage::PartialSavePart::PartialSavePart(size_t offset, size_t size)
    : offset(offset)
    , size(size)
{}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
VirtualStorage::VirtualStorage()
    : m_isChanged(false)
    , m_changedMask(0ull)
{

}

//////////////////////////////////////////////////////////
void VirtualStorage::Init(const std::vector<StorageUnit>& units)
{
    size_t storageSize = 0;
    for (auto unit : units)
    {
        if (m_units.find(unit.name) != m_units.end())
        {
            eCDebug ( LOG_CATEGORY_LIBS ) << "Duplicate parameter name : " <<  unit.name;
            Assert("Duplicate parameter name");
        }
        unit.storageOffset = storageSize;
        unit.size = GetUnitSize(unit.type);
        auto iter = GetStringToType().find(unit.type);
        if (GetStringToType().end() == iter)
        {
            eCDebug ( LOG_CATEGORY_LIBS ) << "Unknown parameter type : " <<  unit.type << ", name : " << unit.name;
            Assert("Unknown parameter type.");
        }
        unit.targetType = iter->second;
        storageSize += GetUnitSize(unit);
        m_units[unit.name] = unit;
    }

    m_storage.resize(storageSize);
}

//////////////////////////////////////////////////////////
size_t VirtualStorage::GetStorageSize() const
{
    return m_storage.size();
}

//////////////////////////////////////////////////////////
bool VirtualStorage::IsChanged() const
{
    return m_isChanged;
}

//////////////////////////////////////////////////////////
const std::vector<u_int8_t> &VirtualStorage::GetBufferAndFlush(std::vector<PartialSavePart>& changedParts)
{
    m_isChanged = false;
    auto sz = GetStorageSize();
    auto sectorSz = sz / 64;
    if (0 == sectorSz)
    {
        sectorSz = 1;
    }
    int sectorNum = 0;
    while(m_changedMask)
    {
        sectorNum += LeadingZeroes2(m_changedMask);
        size_t offset = sectorNum * sectorSz;
        size_t currentSectorSz = sectorSz;
        if (sectorNum == 63)
        {
            currentSectorSz = sz - offset;
        }
        changedParts.push_back(PartialSavePart(offset, currentSectorSz));
        sectorNum++;
    }
    m_changedMask = 0ull;
    return m_storage;
}

//////////////////////////////////////////////////////////
void VirtualStorage::ApplyBuffer(const std::vector<u_int8_t>& buffer)
{
    if (buffer.size() != m_storage.size())
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Applying different size buffer " <<  buffer.size() << ", " << m_storage.size();
        Assert("Applying different size buffer.");
    }

    m_storage = buffer;
}

//////////////////////////////////////////////////////////
size_t VirtualStorage::GetUnitSize(const std::string& unitType) const
{
    auto iter = GetStringToType().find(unitType);
    if (iter == GetStringToType().end())
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unsupported data type(1) " <<  unitType;
        Assert("Unsupported data type(1).");
    }

    auto type = iter->second;
    switch (type) {
    case VS_SupportedTypes::Type_char       :   return sizeof(char);
    case VS_SupportedTypes::Type_int8       :   return sizeof(int8_t);
    case VS_SupportedTypes::Type_uint8      :   return sizeof(u_int8_t);
    case VS_SupportedTypes::Type_int16      :   return sizeof(int16_t);
    case VS_SupportedTypes::Type_uint16     :   return sizeof(u_int16_t);
    case VS_SupportedTypes::Type_int32      :   return sizeof(int32_t);
    case VS_SupportedTypes::Type_uint32     :   return sizeof(u_int32_t);
    case VS_SupportedTypes::Type_int64      :   return sizeof(int64_t);
    case VS_SupportedTypes::Type_uint64     :   return sizeof(u_int64_t);
    case VS_SupportedTypes::Type_float      :   return sizeof(float);
    case VS_SupportedTypes::Type_double     :   return sizeof(double);
    case VS_SupportedTypes::Type_bool       :   return sizeof(bool);
    case VS_SupportedTypes::Type_string     :   return sizeof(char);
    case VS_SupportedTypes::Type_currency   :   return sizeof(u_int64_t);
    case VS_SupportedTypes::Type_credits    :   return sizeof(u_int64_t);
    case VS_SupportedTypes::Type_percents   :   return sizeof(u_int64_t);
    default:
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unsupported data type " <<  unitType << ", " << (int)type;
        Assert("Unsupported data type.");
        break;
    }
    return 0;
}

//////////////////////////////////////////////////////////
size_t VirtualStorage::GetUnitSize(const StorageUnit& unit) const
{
    size_t elementSize = GetUnitSize(unit.type);
    size_t count = 1, sizeFieldBytes = 0;
    if ( unit.isArray || unit.type == "string" )
    {
        count = unit.maxArraySize;
        sizeFieldBytes = 2;
    }
    return elementSize * count + sizeFieldBytes;
}

//////////////////////////////////////////////////////////
const std::map<std::string, VS_SupportedTypes>& VirtualStorage::GetStringToType() const
{
    return stringToType;
}

//////////////////////////////////////////////////////////
void VirtualStorage::_saveBaseValue(const void* valuePtr, size_t offset, size_t size)
{
    const u_int8_t* ptr = (const u_int8_t*)valuePtr;
    for (size_t i = 0; i < size; i++)
    {
        m_storage[offset + i] = ptr[i];
        _markAsChanged(offset + i);
    }
}

//////////////////////////////////////////////////////////
void VirtualStorage::_loadBaseValue(void* valuePtr, size_t offset, size_t size) const
{
    u_int8_t* ptr = (u_int8_t*)valuePtr;
    for (size_t i = 0; i < size; i++)
    {
        ptr[i] = m_storage[offset + i];
    }
}

//////////////////////////////////////////////////////////
void VirtualStorage::_markAsChanged(size_t offset)
{
    auto sz = GetStorageSize();
    auto sectorSz = sz / 64;
    if (0 == sectorSz)
    {
        sectorSz = 1;
    }

    auto sectorNum = offset / sectorSz;
    if (sectorNum > 63)
    {
        sectorNum = 63;
    }
    m_changedMask |= (1ull << sectorNum);
}

//////////////////////////////////////////////////////////
void VirtualStorage::SaveUnit(const std::string& unitName, const std::string& value)
{
    m_isChanged = true;
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non existing string parameter " <<  unitName;
        Assert("Saving non existing string parameter.");
        return;
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_string)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving string as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Saving string as different data type.");
        return;
    }
    uint16_t elementsCount = value.size();
    if (elementsCount > unit.maxArraySize)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Out of bounds string saving : " << unit.name << ", max size : " << unit.maxArraySize << ", currenct size : " << elementsCount;
        Assert("Out of bounds string saving.");
        return;
    }
    size_t offset = unit.storageOffset;
    _saveUnit(VS_SupportedTypes::Type_uint16, offset, 2, elementsCount);
    offset += 2;
    for(const auto& v : value)
    {
        _saveUnit(VS_SupportedTypes::Type_char, offset, unit.size, v);
        offset += unit.size;
    }
}

//////////////////////////////////////////////////////////
void VirtualStorage::SaveUnit(const std::string& unitName, const char* value)
{
    m_isChanged = true;
    std::string str = std::string(value);
    SaveUnit(unitName, str);
}

//////////////////////////////////////////////////////////
void VirtualStorage::SaveUnit(const std::string& unitName, const Currency& value)
{
    m_isChanged = true;
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non existing Currency parameter " <<  unitName;
        Assert("Saving non existing Currency parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_currency)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving currency as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Saving currency as different data type.");
    }
    int64_t rawNumber = value.GetRawNumber();
    _saveBaseValue( &rawNumber, unit.storageOffset, unit.size );
}

//////////////////////////////////////////////////////////
void VirtualStorage::SaveUnit(const std::string& unitName, const std::vector<Currency>& value, size_t start, size_t count)
{
    if (count == 0)
    {
        count = value.size() - start;
    }
    if (start >= value.size() || start + count > value.size())
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving array parameter out of range : " <<  unitName << " " << value.size() << " " << start << " " << count;
        Assert("Saving array parameter out of range.");
    }
    m_isChanged = true;
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non existing Currency array parameter " <<  unitName;
        Assert("Saving non existing Currency array parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_currency)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving currency array as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Saving currency array as different data type.");
    }

    if (false == unit.isArray)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non array currency parameter as array " <<  unitName << ", type : " << unit.type;
        Assert("Saving non array currency parameter as array.");

    }

    uint16_t elementsCount = value.size();
    if (elementsCount > unit.maxArraySize)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Out of bounds saving : " << unit.name << ", max size : " << unit.maxArraySize << ", currenct size : " << elementsCount;
        Assert("Out of bounds saving.");
    }
    size_t offset = unit.storageOffset;
    _saveUnit(VS_SupportedTypes::Type_uint16, offset, 2, elementsCount);
    offset += 2;
    offset += start * unit.size;
    for(size_t i = start; i < start + count; i++)
    {
        _saveUnit(VS_SupportedTypes::Type_int64, offset, unit.size, value[i].GetRawNumber());
        offset += unit.size;
    }
}

//////////////////////////////////////////////////////////
void VirtualStorage::SaveUnit(const std::string& unitName, const Credits& value)
{
    m_isChanged = true;
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non existing Credits parameter " <<  unitName;
        Assert("Saving non existing Credits parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_credits)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving credits as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Saving credits as different data type.");
    }
    int64_t rawNumber = value.GetRawNumber();
    _saveBaseValue( &rawNumber, unit.storageOffset, unit.size );
}

//////////////////////////////////////////////////////////
void VirtualStorage::SaveUnit(const std::string& unitName, const std::vector<Credits>& value, size_t start, size_t count)
{
    if (count == 0)
    {
        count = value.size() - start;
    }
    if (start >= value.size() || start + count > value.size())
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving array parameter out of range : " <<  unitName << " " << value.size() << " " << start << " " << count;
        Assert("Saving array parameter out of range.");
    }
    m_isChanged = true;
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non existing Credits array parameter " <<  unitName;
        Assert("Saving non existing Credits array parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_credits)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving credits array as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Saving credits array as different data type.");
    }

    if (false == unit.isArray)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non array credits parameter as array " <<  unitName << ", type : " << unit.type;
        Assert("Saving non array credits parameter as array.");

    }

    uint16_t elementsCount = value.size();
    if (elementsCount > unit.maxArraySize)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Out of bounds saving : " << unit.name << ", max size : " << unit.maxArraySize << ", currenct size : " << elementsCount;
        Assert("Out of bounds saving.");
    }
    size_t offset = unit.storageOffset;
    _saveUnit(VS_SupportedTypes::Type_uint16, offset, 2, elementsCount);
    offset += 2;
    offset += start * unit.size;
    for(size_t i = start; i < start + count; i++)
    {
        _saveUnit(VS_SupportedTypes::Type_int64, offset, unit.size, value[i].GetRawNumber());
        offset += unit.size;
    }
}

//////////////////////////////////////////////////////////
void VirtualStorage::SaveUnit(const std::string& unitName, const Percents& value)
{
    m_isChanged = true;
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non existing Percents parameter " <<  unitName;
        Assert("Saving non existing Percents parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_percents)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving percents as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Saving percents as different data type.");
    }
    int64_t rawNumber = value.GetRawNumber();
    _saveBaseValue( &rawNumber, unit.storageOffset, unit.size );
}

//////////////////////////////////////////////////////////
void VirtualStorage::SaveUnit(const std::string& unitName, const std::vector<Percents>& value, size_t start, size_t count)
{
    if (count == 0)
    {
        count = value.size() - start;
    }
    if (start >= value.size() || start + count > value.size())
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving array parameter out of range : " <<  unitName << " " << value.size() << " " << start << " " << count;
        Assert("Saving array parameter out of range.");
    }
    m_isChanged = true;
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non existing Percents array parameter " <<  unitName;
        Assert("Saving non existing Percents array parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_percents)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving percents array as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Saving percents array as different data type.");
    }

    if (false == unit.isArray)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving non array percents parameter as array " <<  unitName << ", type : " << unit.type;
        Assert("Saving non array percents parameter as array.");

    }

    uint16_t elementsCount = value.size();
    if (elementsCount > unit.maxArraySize)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Out of bounds saving : " << unit.name << ", max size : " << unit.maxArraySize << ", currenct size : " << elementsCount;
        Assert("Out of bounds saving.");
    }
    size_t offset = unit.storageOffset;
    _saveUnit(VS_SupportedTypes::Type_uint16, offset, 2, elementsCount);
    offset += 2;
    offset += start * unit.size;
    for(size_t i = start; i < start + count; i++)
    {
        _saveUnit(VS_SupportedTypes::Type_int64, offset, unit.size, value[i].GetRawNumber());
        offset += unit.size;
    }
}

//////////////////////////////////////////////////////////
void VirtualStorage::LoadUnit(const std::string& unitName, std::string& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non existing string parameter " <<  unitName;
        Assert("Loading non existing string parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_string)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading string from different data type " <<  unitName << ", type : " << unit.type;
        Assert("Loading string from different data type.");
    }
    uint16_t elementsCount;
    size_t offset = unit.storageOffset;
    _loadUnit(VS_SupportedTypes::Type_uint16, offset, 2, elementsCount);

    offset += 2;
    value.clear();
    for(size_t i = 0; i < elementsCount; i++)
    {
        char v;
        _loadUnit(VS_SupportedTypes::Type_char, offset, unit.size, v);
        value.push_back(v);
        offset += unit.size;
    }
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////


























//////////////////////////////////////////////////////////
void VirtualStorage::LoadUnit(const std::string& unitName, Currency& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non existing Currency parameter " <<  unitName;
        Assert("Loading non existing Currency parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_currency)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading currency from different data type " <<  unitName << ", type : " << unit.type;
        Assert("Loading currency from different data type.");
    }
    int64_t rawNumber;
    _loadBaseValue(&rawNumber, unit.storageOffset, unit.size );
    value = Currency::FromCents(rawNumber);
}

//////////////////////////////////////////////////////////
void VirtualStorage::LoadUnit(const std::string& unitName, std::vector<Currency>& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non existing Currency array parameter " <<  unitName;
        Assert("Loading non existing Currency array parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_currency)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading currency array from different data type " <<  unitName << ", type : " << unit.type;
        Assert("Loading currency array from different data type.");
    }

    if (false == unit.isArray)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non array currency parameter as array " <<  unitName << ", type : " << unit.type;
        Assert("Loading non array currency parameter as array.");

    }

    uint16_t elementsCount;
    size_t offset = unit.storageOffset;
    _loadUnit(VS_SupportedTypes::Type_uint16, offset, 2, elementsCount);
    offset += 2;
    value.clear();
    for(size_t i = 0; i < elementsCount; i++)
    {
        int64_t rawNumber;
        _loadBaseValue(&rawNumber, offset, unit.size);
        value.push_back(Currency::FromCents(rawNumber));
        offset += unit.size;
    }
}

//////////////////////////////////////////////////////////
void VirtualStorage::LoadUnit(const std::string& unitName, Credits& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non existing Credits parameter " <<  unitName;
        Assert("Loading non existing Credits parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_credits)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading credits as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Loading credits as different data type.");
    }
    int64_t rawNumber;
    _loadBaseValue(&rawNumber, unit.storageOffset, unit.size );
    value = Credits(FromRaw(rawNumber));
}

//////////////////////////////////////////////////////////
void VirtualStorage::LoadUnit(const std::string& unitName, std::vector<Credits>& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non existing Credits array parameter " <<  unitName;
        Assert("Loading non existing Credits array parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_credits)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading credits array as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Loading credits array as different data type.");
    }

    if (false == unit.isArray)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non array credits parameter as array " <<  unitName << ", type : " << unit.type;
        Assert("Loading non array credits parameter as array.");

    }

    uint16_t elementsCount;
    size_t offset = unit.storageOffset;
    _loadUnit(VS_SupportedTypes::Type_uint16, offset, 2, elementsCount);
    offset += 2;
    value.clear();
    for(size_t i = 0; i < elementsCount; i++)
    {
        int64_t rawNumber;
        _loadBaseValue(&rawNumber, offset, unit.size);
        value.push_back(Credits(FromRaw(rawNumber)));
        offset += unit.size;
    }
}

//////////////////////////////////////////////////////////
void VirtualStorage::LoadUnit(const std::string& unitName, Percents& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non existing Percents parameter " <<  unitName;
        Assert("Loading non existing Percents parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_percents)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading percents as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Loading percents as different data type.");
    }
    int64_t rawNumber;
    _loadBaseValue(&rawNumber, unit.storageOffset, unit.size );
    value = Percents::FromRawNumber(rawNumber);
}

//////////////////////////////////////////////////////////
void VirtualStorage::LoadUnit(const std::string& unitName, std::vector<Percents>& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non existing Percents array parameter " <<  unitName;
        Assert("Loading non existing Percents array parameter.");
    }
    const auto& unit = iter->second;
    if (unit.targetType != VS_SupportedTypes::Type_percents)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading percents array as different data type " <<  unitName << ", type : " << unit.type;
        Assert("Loading percents array as different data type.");
    }

    if (false == unit.isArray)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading non array percents parameter as array " <<  unitName << ", type : " << unit.type;
        Assert("Loading non array percents parameter as array.");

    }

    uint16_t elementsCount;
    size_t offset = unit.storageOffset;
    _loadUnit(VS_SupportedTypes::Type_uint16, offset, 2, elementsCount);
    offset += 2;
    value.clear();
    for(size_t i = 0; i < elementsCount; i++)
    {
        int64_t rawNumber;
        _loadBaseValue(&rawNumber, offset, unit.size);
        value.push_back(Percents::FromRawNumber(rawNumber));
        offset += unit.size;
    }
}

