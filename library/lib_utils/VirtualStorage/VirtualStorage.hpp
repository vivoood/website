
//////////////////////////////////////////////////////////
template<typename ValueType>
void VirtualStorage::SaveUnit(const std::string& unitName, const ValueType& value)
{
    m_isChanged = true;
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving unknown parameter " <<  unitName;
        Assert("Saving unknown parameter.");
    }
    const auto& unit = iter->second;
    switch(unit.targetType)
    {
    case VS_SupportedTypes::Type_char   :
    case VS_SupportedTypes::Type_int8   :
    case VS_SupportedTypes::Type_uint8  :
    case VS_SupportedTypes::Type_int16  :
    case VS_SupportedTypes::Type_uint16 :
    case VS_SupportedTypes::Type_int32  :
    case VS_SupportedTypes::Type_uint32 :
    case VS_SupportedTypes::Type_int64  :
    case VS_SupportedTypes::Type_uint64 :
    case VS_SupportedTypes::Type_float  :
    case VS_SupportedTypes::Type_double :
    case VS_SupportedTypes::Type_bool   :
        _saveUnit(unit.targetType , unit.storageOffset, unit.size, value);
        break;
    //
    case VS_SupportedTypes::Type_string     :
    case VS_SupportedTypes::Type_currency   :
    case VS_SupportedTypes::Type_credits    :
    case VS_SupportedTypes::Type_percents   :
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unexpected template save function call : " << unitName;
        Assert("Unexpected template save function call.");
        break;
    default:
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unsupported data type " <<  unit.type << ", " << (int)unit.targetType;
        Assert("Unsupported data type.");
        break;
    }
}

//////////////////////////////////////////////////////////
template<typename ValueType>
void VirtualStorage::LoadUnit(const std::string& unitName, ValueType& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading unknown parameter " <<  unitName;
        Assert("Loading unknown parameter.");
    }
    const auto& unit = iter->second;
    switch(unit.targetType)
    {
    case VS_SupportedTypes::Type_char   :
    case VS_SupportedTypes::Type_int8   :
    case VS_SupportedTypes::Type_uint8  :
    case VS_SupportedTypes::Type_int16  :
    case VS_SupportedTypes::Type_uint16 :
    case VS_SupportedTypes::Type_int32  :
    case VS_SupportedTypes::Type_uint32 :
    case VS_SupportedTypes::Type_int64  :
    case VS_SupportedTypes::Type_uint64 :
    case VS_SupportedTypes::Type_float  :
    case VS_SupportedTypes::Type_double :
    case VS_SupportedTypes::Type_bool   :
        _loadUnit(unit.targetType, unit.storageOffset, unit.size, value);
        break;
    //
    case VS_SupportedTypes::Type_string     :
    case VS_SupportedTypes::Type_currency   :
    case VS_SupportedTypes::Type_credits    :
    case VS_SupportedTypes::Type_percents   :
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unexpected template load function call : " << unitName;
        Assert("Unexpected template load function call.");
        break;
    default:
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unsupported load data type " <<  unit.type << ", " << (int)unit.targetType;
        Assert("Unsupported load data type.");
        break;
    }
}

//////////////////////////////////////////////////////////
template<typename ValueType>
void VirtualStorage::_saveUnit(VS_SupportedTypes type, size_t offset, size_t size , const ValueType& value)
{
    switch (type) {
    case VS_SupportedTypes::Type_char   :{ auto v = static_cast<char>(value);      _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_int8   :{ auto v = static_cast<int8_t>(value);    _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_uint8  :{ auto v = static_cast<u_int8_t>(value);   _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_int16  :{ auto v = static_cast<int16_t>(value);   _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_uint16 :{ auto v = static_cast<u_int16_t>(value);  _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_int32  :{ auto v = static_cast<int32_t>(value);   _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_uint32 :{ auto v = static_cast<u_int32_t>(value);  _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_int64  :{ auto v = static_cast<int64_t>(value);   _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_uint64 :{ auto v = static_cast<u_int64_t>(value);  _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_float  :{ auto v = static_cast<float>(value);     _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_double :{ auto v = static_cast<double>(value);    _saveBaseValue(&v, offset, size); } break;
    case VS_SupportedTypes::Type_bool   :{ auto v = static_cast<bool>(value);      _saveBaseValue(&v, offset, size); } break;
    //
    case VS_SupportedTypes::Type_string     :
    case VS_SupportedTypes::Type_currency   :
    case VS_SupportedTypes::Type_credits    :
    case VS_SupportedTypes::Type_percents   :
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unexpected template save function call : " << (int)type;
        Assert("Unexpected template save function call.");
        break;
    default:
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unsupported data type " << (int)type;
        Assert("Unsupported data type.");
        break;
    }
}

//////////////////////////////////////////////////////////
template<typename ValueType>
void VirtualStorage::_loadUnit(VS_SupportedTypes type, size_t offset, size_t size , ValueType& value) const
{
    switch (type) {
    case VS_SupportedTypes::Type_char   :{ char v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_int8   :{ int8_t v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_uint8  :{ uint8_t v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_int16  :{ int16_t v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_uint16 :{ uint16_t v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_int32  :{ int32_t v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_uint32 :{ uint32_t v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_int64  :{ int64_t v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_uint64 :{ uint64_t v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_float  :{ float v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_double :{ double v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    case VS_SupportedTypes::Type_bool   :{ bool v; _loadBaseValue(&v, offset, size);  value = static_cast<ValueType>(v); } break;
    //
    case VS_SupportedTypes::Type_string     :
    case VS_SupportedTypes::Type_currency   :
    case VS_SupportedTypes::Type_credits    :
    case VS_SupportedTypes::Type_percents   :
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unexpected template load function call : " << (int)type;
        Assert("Unexpected template load function call.");
        break;
    default:
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unsupported data type load" << (int)type;
        Assert("Unsupported data type load.");
        break;
    }
}

//////////////////////////////////////////////////////////
template<typename ValueType>
void VirtualStorage::SaveUnit(const std::string& unitName, const std::vector<ValueType>& value, size_t start, size_t count)
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
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving unknown parameter " <<  unitName;
        Assert("Saving unknown parameter.");
    }
    const auto& unit = iter->second;
    if (false == unit.isArray)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Saving array to no array parameter " <<  unit.name << ", type : " << unit.type;
        Assert("Saving array to no array parameter.");

    }

    switch (unit.targetType) {
    case VS_SupportedTypes::Type_char  :
    case VS_SupportedTypes::Type_int8  :
    case VS_SupportedTypes::Type_uint8 :
    case VS_SupportedTypes::Type_int16 :
    case VS_SupportedTypes::Type_uint16:
    case VS_SupportedTypes::Type_int32 :
    case VS_SupportedTypes::Type_uint32:
    case VS_SupportedTypes::Type_int64 :
    case VS_SupportedTypes::Type_uint64:
    case VS_SupportedTypes::Type_float :
    case VS_SupportedTypes::Type_double:
    case VS_SupportedTypes::Type_bool  :
    {
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
            _saveUnit(unit.targetType, offset, unit.size, value[i]);
            offset += unit.size;
        }
    }
    break;
    //
    case VS_SupportedTypes::Type_string     :
    case VS_SupportedTypes::Type_currency   :
    case VS_SupportedTypes::Type_credits    :
    case VS_SupportedTypes::Type_percents   :
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unexpected template save function call : " << unitName;
        Assert("Unexpected template save function call.");
        break;
    default:
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unsupported data type " <<  unit.type << ", " << (int)unit.targetType;
        Assert("Unsupported data type.");
        break;
    }
}

//////////////////////////////////////////////////////////
template<typename ValueType>
void VirtualStorage::LoadUnit(const std::string& unitName, std::vector<ValueType>& value) const
{
    auto iter = m_units.find(unitName);
    if (m_units.end() == iter)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading unknown parameter " <<  unitName;
        Assert("Loading unknown parameter.");
    }
    const auto& unit = iter->second;
    if (false == unit.isArray)
    {
        eCDebug ( LOG_CATEGORY_LIBS ) << "Loading array from no array parameter " <<  unit.name << ", type : " << unit.type;
        Assert("Loading array from no array parameter.");
    }

    value.clear();
    switch (unit.targetType) {
    case VS_SupportedTypes::Type_char  :
    case VS_SupportedTypes::Type_int8  :
    case VS_SupportedTypes::Type_uint8 :
    case VS_SupportedTypes::Type_int16 :
    case VS_SupportedTypes::Type_uint16:
    case VS_SupportedTypes::Type_int32 :
    case VS_SupportedTypes::Type_uint32:
    case VS_SupportedTypes::Type_int64 :
    case VS_SupportedTypes::Type_uint64:
    case VS_SupportedTypes::Type_float :
    case VS_SupportedTypes::Type_double:
    case VS_SupportedTypes::Type_bool  :
    {
        uint16_t elementsCount;
        _loadUnit(VS_SupportedTypes::Type_uint16, unit.storageOffset, 2, elementsCount );

        size_t offset = unit.storageOffset + 2;
        for(size_t i = 0; i < elementsCount; i++)
        {
            ValueType v;
            _loadUnit(unit.targetType, offset, unit.size, v);
            value.push_back(v);
            offset += unit.size;
        }
    }
    break;
    //
    case VS_SupportedTypes::Type_string     :
    case VS_SupportedTypes::Type_currency   :
    case VS_SupportedTypes::Type_credits    :
    case VS_SupportedTypes::Type_percents   :
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unexpected template load function call : " << unitName;
        Assert("Unexpected template load function call.");
        break;
    default:
        eCDebug ( LOG_CATEGORY_LIBS ) << "Unsupported load data type " <<  unit.type << ", " << (int)unit.targetType;
        Assert("Unsupported load data type.");
        break;
    }
}
