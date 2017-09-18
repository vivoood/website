#ifndef COMPONENTMACROENGINE_H
#define COMPONENTMACROENGINE_H

//
// Declaration of components required values
#define COMP_DECLARE_REQ_VALUE(type, valName, ...)  \
private:                                            \
    type    m_##valName;                            \
    bool    m_has_##valName;                        \

//
// Declaration of components NOT required values
#define COMP_DECLARE_NOT_REQ_VALUE(type, valName, ...)   \
private:                                            \
    type    m_##valName;                            \
    bool    m_has_##valName;                        \

//
// Implementation of required values loader
#define COMP_IMPLEMENT_REQ_LOADER(type, valName, ...)    \
    m_has_##valName = Read(xmlNode, #valName, m_##valName);  \
    if (false == m_has_##valName)                   \
    {                                               \
        COMP_LOG << "REQUIRED value not set error : " << #valName << " in " << GetComponentName();    \
        COMP_ASSERT("");                                    \
        return false;                               \
    }                                               \

//
// Implementation of NOT required values loader
#define COMP_IMPLEMENT_NOT_REQ_LOADER(type, valName, ...)\
    m_has_##valName = Read(xmlNode, #valName, m_##valName);  \

//
// Implementation of required values bin loader
#define COMP_IMPLEMENT_REQ_BIN_LOADER(type, valName, ...)                                                   \
    if ((!(compFields >> m_has_##valName)) || (!m_has_##valName))                                           \
    {                                                                                                       \
        COMP_LOG << "REQUIRED value not set error reading : " << #valName << " in " << GetComponentName();  \
        COMP_ASSERT("");                                                                                    \
        return false;                                                                                       \
    }                                                                                                       \
    if (!(compFields >> m_##valName))                                                                       \
    {                                                                                                       \
        COMP_LOG << "Error reading value : " << #valName << " in " << GetComponentName();                   \
        COMP_ASSERT("");                                                                                    \
        return false;                                                                                       \
    }                                                                                                       \

//
// Implementation of NOT required values bin loader
#define COMP_IMPLEMENT_NOT_REQ_BIN_LOADER(type, valName, ...)                                       \
    if (!(compFields >> m_has_##valName))                                                           \
    {                                                                                               \
        COMP_LOG << "Cant read 'has' field error : " << #valName << " in " << GetComponentName();   \
        COMP_ASSERT("");                                                                            \
        return false;                                                                               \
    }                                                                                               \
    if ((Has_##valName()) && (!(compFields >> m_##valName)))                                        \
    {                                                                                               \
        COMP_LOG << "Cant read field error : " << #valName << " in " << GetComponentName();         \
        COMP_ASSERT("");                                                                            \
        return false;                                                                               \
    }                                                                                               \

//
// Implementation of binary loader
#define COMP_IMPLEMENT_BIN_LOAD(VAL_ITERATOR, compName)                             \
    egt::iUniStream compFields;                                                     \
    inputStream >> egt::iUniInplace(compFields);                                    \
    VAL_ITERATOR(COMP_IMPLEMENT_REQ_BIN_LOADER, COMP_IMPLEMENT_NOT_REQ_BIN_LOADER)      \

//
// Implementation of required values hash calculator
#define COMP_IMPLEMENT_REQ_HASH(type, valName, ...)    \
        hashes.push_back(GetFieldHash< type >(#valName, fieldPos++, true) );    \

//
// Implementation of not required values hash calculator
#define COMP_IMPLEMENT_NOT_REQ_HASH(type, valName, ...)    \
        hashes.push_back(GetFieldHash< type >(#valName, fieldPos++, false) );    \

//
// Implementation of required values writer
#define COMP_IMPLEMENT_REQ_WRITER(type, valName, ...)                        \
    if (Has_##valName() == false)                                       \
    {                                                                   \
        COMP_LOG << "REQUIRED value not set error before saving : " << #valName << " in " << GetComponentName();    \
        COMP_ASSERT("");                                                \
        return false;                                                   \
    }                                                                   \
    if (false == IBaseComponent::Write(node, #valName, m_##valName))    \
    {                                                                   \
        COMP_LOG << "Cant save field " << #valName;                     \
        return false;                                                   \
    }                                                                   \

//
// Implementation of NOT required values writer
#define COMP_IMPLEMENT_NOT_REQ_WRITER(type, valName, ...)            \
    if ((Has_##valName()) && (false == IBaseComponent::Write(node, #valName, m_##valName))) \
    {                                                                                       \
        COMP_LOG << "Cant save field " << #valName;                                         \
        return false;                                                                       \
    }                                                                                       \

//
// Implementation of required values binary writer
#define COMP_IMPLEMENT_REQ_BIN_WRITER(type, valName, ...)   \
    if (Has_##valName() == false)                                       \
    {                                                                   \
        COMP_LOG << "REQUIRED value not set error before saving : " << #valName << " in " << GetComponentName();    \
        COMP_ASSERT("");                                                \
        return false;                                                   \
    }                                                                   \
    if (!(compFields << true << m_##valName))                           \
    {                                                                   \
        COMP_LOG << "Cant save field " << #valName;                     \
        return false;                                                   \
    }                                                                   \

//
// Implementation of NOT required values writer
#define COMP_IMPLEMENT_NOT_REQ_BIN_WRITER(type, valName, ...)                                   \
    if (Has_##valName())                                                                        \
    {                                                                                           \
        if (!(compFields << true << m_##valName))                                               \
        {                                                                                       \
            COMP_LOG << "Cant save field " << #valName;                                         \
            return false;                                                                       \
        }                                                                                       \
    } else                                                                                      \
    {                                                                                           \
        if (!(compFields << false))                                                              \
        {                                                                                       \
            COMP_LOG << "Cant save 'has' field " << #valName;                                   \
            return false;                                                                       \
        }                                                                                       \
    }                                                                                           \

//
// Implementation of required values binary writer
#define COMP_IMPLEMENT_REQ_BIN_MSG__WRITER(type, valName, ...)                                  \
    if (Has_##valName() == false)                                                               \
    {                                                                                           \
        COMP_LOG << "REQUIRED value not set error before saving to bin msg : " << #valName << " in " << GetComponentName();    \
        COMP_ASSERT("");                                                                        \
    }                                                                                           \
    msg.AddValue(#valName, m_##valName);                                                         \
                                                                                                \

//
// Implementation of not required values binary writer
#define COMP_IMPLEMENT_NOT_REQ_BIN_MSG__WRITER(type, valName, ...)                              \
    if (Has_##valName() == true)                                                                \
    {                                                                                           \
        msg.AddValue(#valName, m_##valName);                                                     \
    }                                                                                           \


//
// Take all fields that are empty and that exist in the argument component 'c'
// and store them in 'this' component
#define COMP_IMPLEMENT_TAKE_EMPTY_FIELDS_FROM(type, valName, ...)           \
    if ( (false == this->Has_##valName()) && (true == c.Has_##valName()))   \
    {                                                                       \
        this->Set_##valName(c.Get_##valName());                             \
        anyChange = true;                                                   \
    }                                                                       \

//
// Implementation of binary serialization
#define COMP_IMPLEMENT_BIN_SERIALIZE(VAL_ITERATOR, compName)                        \
    egt::oUniStream compFields;                                                     \
    outStream >> egt::oUniInplace(compFields);                                      \
    VAL_ITERATOR(COMP_IMPLEMENT_REQ_BIN_WRITER, COMP_IMPLEMENT_NOT_REQ_BIN_WRITER)  \
    outStream << compFields;                                                        \

//
// Implementation of required values getter
#define COMP_IMPLEMENT_REQ_GETTERS(type, valName, ...)                  \
public:                                                                 \
    bool Has_##valName() const { return m_has_##valName; };             \
__VA_ARGS__                                                             \
    const type& Get_##valName() const                                   \
    {                                                                   \
        if(false == Has_##valName())                                    \
        {                                                               \
            COMP_LOG << "Not initialized REQUIRED variable usage : "    \
                << #valName << " in " << GetComponentName();            \
            COMP_ASSERT("");                                            \
        }                                                               \
        return m_##valName;                                             \
    }                                                                   \
    void Set_##valName(const type& newVal)                              \
        { m_##valName = newVal; m_has_##valName = true; }               \
    void Clear_##valName()                                              \
        { m_has_##valName = false; m_##valName = type (); }             \
//
#define COMP_DECLARE_COMP_FIELDS_ENUM(type, valName, ...)    valName,

//
// Implementation of NOT required values getters
#define COMP_IMPLEMENT_NOT_REQ_GETTERS(type, valName, ...)      \
public:                                                         \
    bool Has_##valName() const                                  \
        {return m_has_##valName;}                               \
__VA_ARGS__ /* you can specify access control here*/            \
    const type& Get_##valName() const                           \
    {                                                           \
        if(false == Has_##valName())                            \
        {                                                       \
            COMP_LOG << "Not initialized variable usage : "     \
                << #valName << " in " << GetComponentName();    \
            COMP_ASSERT("");                                    \
        }                                                       \
        return m_##valName;                                     \
    }                                                           \
    void Set_##valName(const type& newVal)                      \
        { m_##valName = newVal; m_has_##valName = true; }       \
    void Clear_##valName()                                      \
        { m_has_##valName = false; m_##valName = type (); }     \

#define IMPLEMENT_COMPONENTS_ENUM(compName, foo)    \
    COMP_ID_##compName,

///////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_COMPONENT_LOADER(compName, foo)               \
    case EComponentId::COMP_ID_##compName:                      \
    {                                                           \
        auto ptr = compName##Component::CreateNewInstance();    \
        if (ptr->BaseLoad<ComponentsFactory>(inputData))          \
        {                                                       \
            return ptr;                                         \
        }                                                       \
        return egt::IBaseComponentPtr(nullptr);                 \
    }                                                           \
    break;                                                      \

///////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_COMPONENT_CREATOR(compName, foo)               \
    case EComponentId::COMP_ID_##compName:                      \
    {                                                           \
        auto ptr = compName##Component::CreateNewInstance();    \
        return ptr;                                             \
    }                                                           \
    break;                                                      \
//

///////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_COMPONENT_MERGER(compName, foo)                                                               \
    case EComponentId::COMP_ID_##compName:                                                                      \
    {                                                                                                           \
        compName##ComponentPtr lowComp = compName##Component::SafeCast(lowPriorityCompPtr);                     \
        if (nullptr == lowComp)                                                                                 \
        {                                                                                                       \
            COMP_LOG    << "Low Component merge cast fail: " << lowPriorityCompPtr->GetComponentName() << ", "  \
                        << lowPriorityCompPtr->GetComponentId() << ", "                                         \
                        << lowPriorityCompPtr->GetNamespaceName();                                              \
            COMP_ASSERT("Low Component merge cast fail");                                                       \
        }                                                                                                       \
        compName##ComponentPtr highComp = compName##Component::SafeCast(highPriorityCompPtr);                   \
        if (nullptr == highComp)                                                                                \
        {                                                                                                       \
            COMP_LOG    << "High Component merge cast fail: " << highPriorityCompPtr->GetComponentName() << "," \
                        << highPriorityCompPtr->GetComponentId() << ", "                                        \
                        << highPriorityCompPtr->GetNamespaceName();                                             \
            COMP_ASSERT("High Component merge cast fail");                                                      \
        }                                                                                                       \
        std::string newHint = "Merged by ("+lowComp->GetComponentHint()+" + "+highComp->GetComponentHint()+")"; \
        compName##ComponentPtr newComp = compName##Component::CreateNewInstance(newHint);                       \
        newComp->FillEmptyFieldsFrom(*highComp);                                                                \
        newComp->FillEmptyFieldsFrom(*lowComp);                                                                 \
        egt::IBaseComponent::AutoMergeContainers(lowPriorityCompPtr, highPriorityCompPtr, newComp);             \
        if (false == compName##Component::MergeValidator(*lowComp, *highComp, *newComp) )                       \
        {                                                                                                       \
            COMP_LOG << "Merging components fail: "  << lowPriorityCompPtr->GetComponentName();                 \
            COMP_ASSERT("Merging components fail");                                                             \
            return nullptr;                                                                                     \
        }                                                                                                       \
        return newComp;                                                                                         \
    }                                                                                                           \
    break;                                                                                                      \

//

#define EGT_COMPONENT_COMMON_DECLARATIONS(VAL_ITERATOR, compName)                                   \
public:                                                                                             \
enum class Fields                                                                                   \
{                                                                                                   \
    VAL_ITERATOR(COMP_DECLARE_COMP_FIELDS_ENUM, COMP_DECLARE_COMP_FIELDS_ENUM)                      \
    _ComponentFieldsCount                                                                           \
};                                                                                                  \
VAL_ITERATOR(COMP_IMPLEMENT_REQ_GETTERS, COMP_IMPLEMENT_NOT_REQ_GETTERS)                            \
public:                                                                                             \
compName##Component();                                                                              \
virtual ~compName##Component();                                                                     \
                                                                                                    \
virtual egt::IComponentId GetComponentId() const;                                                   \
virtual std::string GetComponentName() const;                                                       \
virtual u_int64_t GetComponentTypeHash() const;                                                     \
virtual std::string GetNamespaceName() const;                                                       \
virtual u_int64_t GetFactoryTypeHash() const;                                                       \
virtual void Clear();                                                                               \
virtual bool IsEmpty() const;                                                                       \
virtual bool IsEqualTo(egt::IBaseComponentPtr compPtr) const;                                       \
virtual void CopyFrom(const egt::IBaseComponent* compPtr);                                          \
virtual egt::IBaseComponentPtr CreateCopy() const;                                                  \
virtual void Serialize(egt::ComponentMsgTypes::LocalMsg& msg);                                           \
virtual void Serialize(egt::ComponentMsgTypes::RemoteMsg& msg);                                          \
    /* REFLECTIONS */                                                                               \
virtual std::map<std::string, egt::IBaseComponent::FieldInfo> _getFieldsInfo() const;               \
virtual egt::IBaseComponent::Field _getField( const std::string& fieldName ) const;                 \
virtual void _setField( const std::string& fieldName, const egt::UniObject& value );                \
virtual void _clearField( const std::string& fieldName );                                           \
                                                                                                    \
bool FillEmptyFieldsFrom(const compName##Component& c);                                             \
static egt::IComponentId GetComponentIdStatic();                                                    \
static std::string GetComponentNameStatic();                                                        \
static std::shared_ptr<compName##Component> CreateNewInstance(std::string hint = std::string());    \
static u_int64_t GetComponentTypeHashStatic();                                                      \
static u_int64_t GetFactoryTypeHashStatic();                                                        \
static compName##ComponentPtr SafeCast(std::shared_ptr<IBaseComponent> compPtr);                    \
static const compName##Component* SafeCastRawPtr(const egt::IBaseComponent* compPtr);               \
static std::string GetNamespaceNameStatic();                                                        \
static bool MergeValidator( const compName##Component& lowPriorityComp,                             \
                            const compName##Component& highPriorityComp,                            \
                            compName##Component& mergedComp);                                       \
                                                                                                    \
/*template<class ManagerType>                                                                 */        \
/*static bool Contain(std::shared_ptr<ManagerType> mgrPtr)                                    */        \
/*{                                                                                           */        \
/*    if (nullptr == mgrPtr)                                                                  */        \
/*    {                                                                                       */        \
/*        COMP_LOG    << "Looking for component in null manager : "                           */        \
/*                    << compName##Component::GetComponentNameStatic();                       */        \
/*        COMP_ASSERT("mrg nullptr.");                                                        */        \
/*        return false;                                                                       */        \
/*    }                                                                                       */        \
/*    return mgrPtr->Contain(compName##Component::GetComponentIdStatic());                    */        \
/*}                                                                                           */        \
                                                                                                    \
template<class ManagerType>                                                                         \
static compName##ComponentPtr SafeGet(std::shared_ptr<ManagerType> mgrPtr)                          \
{                                                                                                   \
    if (nullptr == mgrPtr)                                                                          \
    {                                                                                               \
        COMP_LOG    << "Looking for component in null manager : "                                   \
                    << compName##Component::GetComponentNameStatic();                               \
        COMP_ASSERT("mrg nullptr.");                                                                \
        return compName##Component::CreateNewInstance();                                            \
    }                                                                                               \
    egt::IBaseComponentPtr basePtr = mgrPtr->GetComponent                                           \
                                (compName##Component::GetComponentIdStatic());                      \
    if (nullptr == basePtr)                                                                         \
    {                                                                                               \
        COMP_LOG    << "Missing component in manager : " << mgrPtr->GetName()                       \
                    << ", " << compName##Component::GetComponentNameStatic();                       \
        COMP_ASSERT("Missing component.");                                                          \
        return compName##Component::CreateNewInstance();                                            \
    }                                                                                               \
    compName##ComponentPtr comp = compName##Component::SafeCast(basePtr);                           \
    if (nullptr == comp)                                                                            \
    {                                                                                               \
        COMP_LOG    << "Component cast error: " << mgrPtr->GetName()                                \
                    << ", " << basePtr->GetComponentName() << ", "                                  \
                    << compName##Component::GetComponentNameStatic();                               \
        COMP_ASSERT("Component cast error");                                                        \
        return compName##Component::CreateNewInstance();                                            \
    }                                                                                               \
    return comp;                                                                                    \
}                                                                                                   \
virtual bool Serialize(egt::oUniStream& outStream) const;                                           \
virtual bool Load(egt::iUniStream& inputStream);                                                    \
protected:                                                                                          \
virtual bool Load(const pugi::xml_node& xmlNode);                                                   \
virtual bool Serialize(pugi::xml_node& node) const;                                                 \
                                                                                                    \
VAL_ITERATOR(COMP_DECLARE_REQ_VALUE, COMP_DECLARE_NOT_REQ_VALUE)                                    \
                                                                                                    \
private:                                                                                            \
static u_int64_t s_structureHash;                                                                   \
static bool s_structureHashCalced;                                                                  \

//
#define IMPLEMENT_COMPONENT_ID_GETTERS(compName, foo)               \
    egt::IComponentId compName##Component::GetComponentId() const   \
    {                                                               \
        return (egt::IComponentId)EComponentId::COMP_ID_##compName; \
    }                                                               \
    egt::IComponentId compName##Component::GetComponentIdStatic()   \
    {                                                               \
        return (egt::IComponentId)EComponentId::COMP_ID_##compName; \
    }                                                               \
    u_int64_t compName##Component::GetFactoryTypeHash() const       \
    {                                                               \
        return GetFactoryTypeHashStatic();                          \
    }                                                               \
    u_int64_t compName##Component::GetFactoryTypeHashStatic()       \
    {                                                               \
        return ComponentsFactory::GetFactoryHash();                 \
    }                                                               \

//
#define IMPLEMENT_COMPONENT_STREAM_OPERATORS(compName, foo)                                     \
namespace egt{                                                                                \
template<>                                                                                      \
oUniStream& operator<< (oUniStream& out, const compName##Component& comp)                       \
{                                                                                               \
    comp.Serialize(out);                                                                        \
    return out;                                                                                 \
}                                                                                               \
template<>                                                                                      \
iUniStream& operator>> (iUniStream& in, compName##Component& comp)                              \
{                                                                                               \
    comp.Load(in);                                                                              \
    return in;                                                                                  \
}                                                                                               \
}                                                                                               \

//
#define IMPLEMENT_COMPONENT_COMMON_METHODS(VAL_ITERATOR, compName, nmSpace)                         \
std::string compName##Component::GetComponentName() const                                           \
{                                                                                                   \
    return #compName;                                                                               \
}                                                                                                   \
std::string compName##Component::GetComponentNameStatic()                                           \
{                                                                                                   \
    return #compName;                                                                               \
}                                                                                                   \
std::shared_ptr<compName##Component> compName##Component::CreateNewInstance(std::string hint)       \
{                                                                                                   \
    auto newInst = std::make_shared< compName##Component >();                                       \
    newInst->SetComponentHint(hint);                                                                \
    newInst->InitOwnWeakPointer(newInst);                                                           \
    return newInst;                                                                                 \
}                                                                                                   \
u_int64_t compName##Component::s_structureHash = 0;                                                 \
bool compName##Component::s_structureHashCalced = false;                                            \
u_int64_t compName##Component::GetComponentTypeHash() const                                         \
{                                                                                                   \
    return GetComponentTypeHashStatic();                                                            \
}                                                                                                   \
u_int64_t compName##Component::GetComponentTypeHashStatic()                                         \
{                                                                                                   \
    if (false == s_structureHashCalced)                                                             \
    {                                                                                               \
        std::vector<u_int64_t> hashes;                                                              \
        int fieldPos = 1;                                                                           \
        VAL_ITERATOR(COMP_IMPLEMENT_REQ_HASH, COMP_IMPLEMENT_NOT_REQ_HASH);                         \
        hashes.push_back(egt::HashConstructor::ConstructHash(#compName));                           \
        hashes.push_back(egt::HashConstructor::ConstructHash(GetNamespaceNameStatic().c_str()));    \
        s_structureHash = egt::HashConstructor::ConstructHash(hashes);                              \
        s_structureHashCalced = true;                                                               \
    }                                                                                               \
    return s_structureHash;                                                                         \
}                                                                                                   \
compName##ComponentPtr compName##Component::SafeCast(std::shared_ptr<egt::IBaseComponent> compPtr)  \
{                                                                                                   \
    if (nullptr == compPtr)                                                                         \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetComponentId() != compName##Component::GetComponentIdStatic())                   \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetComponentTypeHash() != compName##Component::GetComponentTypeHashStatic())       \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetFactoryTypeHash() != compName##Component::GetFactoryTypeHashStatic())           \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    compName##ComponentPtr ptr = std::dynamic_pointer_cast<compName##Component>(compPtr);           \
    return ptr;                                                                                     \
}                                                                                                   \
const compName##Component* compName##Component::SafeCastRawPtr(const egt::IBaseComponent* compPtr)  \
{                                                                                                   \
    if (nullptr == compPtr)                                                                         \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetComponentId() != compName##Component::GetComponentIdStatic())                   \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetComponentTypeHash() != compName##Component::GetComponentTypeHashStatic())       \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    if (compPtr->GetFactoryTypeHash() != compName##Component::GetFactoryTypeHashStatic())           \
    {                                                                                               \
        return nullptr;                                                                             \
    }                                                                                               \
    const compName##Component* ptr = static_cast<const compName##Component*>(compPtr);              \
    return ptr;                                                                                     \
}                                                                                                   \
std::string compName##Component::GetNamespaceNameStatic()                                           \
{                                                                                                   \
    return std::string( FACTORY_NAMESPACE_STRING );                                                 \
}                                                                                                   \
std::string compName##Component::GetNamespaceName() const                                           \
{                                                                                                   \
    return GetNamespaceNameStatic();                                                                \
}                                                                                                   \
bool compName##Component::FillEmptyFieldsFrom(const compName##Component& c)                         \
{                                                                                                   \
    bool anyChange = false;                                                                         \
    VAL_ITERATOR(COMP_IMPLEMENT_TAKE_EMPTY_FIELDS_FROM, COMP_IMPLEMENT_TAKE_EMPTY_FIELDS_FROM);     \
    return anyChange;                                                                               \
}                                                                                                   \
void compName##Component::Clear()                                                                   \
{                                                                                                   \
    VAL_ITERATOR(COMP_CLEAR_VALUE, COMP_CLEAR_VALUE);                                               \
}                                                                                                   \
bool compName##Component::IsEmpty() const                                                           \
{                                                                                                   \
    VAL_ITERATOR(COMP_CHECK_IS_EMPTY_VALUE, COMP_CHECK_IS_EMPTY_VALUE);                             \
    return true;                                                                                    \
}                                                                                                   \
bool compName##Component::IsEqualTo(egt::IBaseComponentPtr compPtr) const                           \
{                                                                                                   \
    compName##ComponentPtr myTypePtr = compName##Component::SafeCast(compPtr);                      \
    if (nullptr == myTypePtr) return false;                                                         \
    VAL_ITERATOR(COMP_CHECK_IS_EQUAL_VALUE, COMP_CHECK_IS_EQUAL_VALUE);                             \
    return true;                                                                                    \
}                                                                                                   \
void compName##Component::CopyFrom(const egt::IBaseComponent* compPtr)                              \
{                                                                                                   \
    const compName##Component* myTypePtr = compName##Component::SafeCastRawPtr(compPtr);            \
    if (nullptr == myTypePtr)                                                                       \
    {                                                                                               \
        COMP_LOG << "Trying to copy from different component type.";                                \
        COMP_ASSERT("Copy from different component type error.");                                   \
        return;                                                                                     \
    }                                                                                               \
    std::string hint = this->GetComponentHint() + " , copy from : " + myTypePtr->GetComponentHint();\
    this->SetComponentHint(hint);                                                                   \
    VAL_ITERATOR(COMP_COPY_FROM_VALUE, COMP_COPY_FROM_VALUE);                                       \
    CopyContainers(*compPtr, *this);                                                                \
}                                                                                                   \
egt::IBaseComponentPtr compName##Component::CreateCopy() const                                      \
{                                                                                                   \
    compName##ComponentPtr myTypePtr = CreateNewInstance();                                         \
    myTypePtr->CopyFrom(this);                                                                      \
    return myTypePtr;                                                                               \
}                                                                                                   \
void compName##Component::Serialize(egt::ComponentMsgTypes::LocalMsg& msg)                               \
{                                                                                                   \
    VAL_ITERATOR(COMP_IMPLEMENT_REQ_BIN_MSG__WRITER, COMP_IMPLEMENT_NOT_REQ_BIN_MSG__WRITER);       \
}                                                                                                   \
void compName##Component::Serialize(egt::ComponentMsgTypes::RemoteMsg& msg)                              \
{                                                                                                   \
    VAL_ITERATOR(COMP_IMPLEMENT_REQ_BIN_MSG__WRITER, COMP_IMPLEMENT_NOT_REQ_BIN_MSG__WRITER);       \
}                                                                                                   \
    /* REFLECTIONS */                                                                               \
std::map<std::string, egt::IBaseComponent::FieldInfo> compName##Component::_getFieldsInfo() const   \
{                                                                                                   \
    std::map<std::string, egt::IBaseComponent::FieldInfo> result;                                   \
    VAL_ITERATOR(IMPL_REQ_REFLECTION_FIELD_VALUE_INFO, IMPL_NOT_REQ_REFLECTION_FIELD_VALUE_INFO)    \
    return result;                                                                                  \
}                                                                                                   \
egt::IBaseComponent::Field compName##Component::_getField( const std::string& fieldName ) const     \
{                                                                                                   \
    if (true == fieldName.empty())                                                                  \
    {}                                                                                              \
    VAL_ITERATOR(IMPL_REQ_REFLECTION_FIELD_VALUE_GETTER, IMPL_REQ_REFLECTION_FIELD_VALUE_GETTER)    \
    COMP_LOG << "Trying to get unexisting field name through reflections : "                        \
             << fieldName << " , " << GetComponentName();                                           \
    COMP_ASSERT("Trying to get unexisting field name through reflections.");                        \
    IBaseComponent::Field emptyField;                                                               \
    emptyField.isSet = false;                                                                       \
    return emptyField;                                                                              \
}                                                                                                   \
void compName##Component::_setField( const std::string& fieldName, const egt::UniObject& value )    \
{                                                                                                   \
    if (true == fieldName.empty())                                                                  \
    {}                                                                                              \
    VAL_ITERATOR(IMPL_REQ_REFLECTION_FIELD_VALUE_SETTER, IMPL_REQ_REFLECTION_FIELD_VALUE_SETTER)    \
    COMP_LOG << "Trying to set unexisting field name through reflections : "                        \
             << fieldName << " , " << GetComponentName();                                           \
    COMP_ASSERT("Trying to set unexisting field name through reflections.");                        \
}                                                                                                   \
void compName##Component::_clearField( const std::string& fieldName )                               \
{                                                                                                   \
    if (true == fieldName.empty())                                                                  \
    {}                                                                                              \
    VAL_ITERATOR(IMPL_REQ_REFLECTION_FIELD_VALUE_CLR, IMPL_REQ_REFLECTION_FIELD_VALUE_CLR)          \
    COMP_LOG << "Trying to clear unexisting field name through reflections : "                      \
             << fieldName << " , " << GetComponentName();                                           \
    COMP_ASSERT("Trying to clear unexisting field name through reflections.");                      \
}                                                                                                   \

//

#define IMPL_REQ_REFLECTION_FIELD_VALUE_GETTER(type, valName, ...)                                  \
    else if ( #valName == fieldName)                                                                \
    {                                                                                               \
        egt::IBaseComponent::Field field;                                                           \
        field.isSet = Has_##valName();                                                              \
        field.value = egt::UniObject();                                                             \
        if (field.isSet) {field.value << Get_##valName();}                                          \
        return field;                                                                               \
    }                                                                                               \

//

#define IMPL_REQ_REFLECTION_FIELD_VALUE_SETTER(type, valName, ...)                                  \
    else if ( #valName == fieldName)                                                                \
    {                                                                                               \
        type tmp = type();                                                                                   \
        value >> tmp;                                                                               \
        Set_##valName(tmp);                                                                         \
        return;                                                                                     \
    }                                                                                               \

//

#define IMPL_REQ_REFLECTION_FIELD_VALUE_CLR(type, valName, ...)                                     \
    else if ( #valName == fieldName)                                                                \
    {                                                                                               \
        Clear_##valName();                                                                          \
        return;                                                                                     \
    }                                                                                               \

//

#define IMPL_REQ_REFLECTION_FIELD_VALUE_INFO(type, valName, ...)                                    \
    {                                                                                               \
        egt::IBaseComponent::FieldInfo fieldInfo;                                                   \
        fieldInfo.fieldName = #valName;                                                             \
        fieldInfo.fieldType = GetTypeName< type >();                                                \
        fieldInfo.isRequired = true;                                                                \
        fieldInfo.isPublic =                                                                        \
                (std::string( #__VA_ARGS__ ) == "" ||                                               \
                std::string( #__VA_ARGS__ ) == "public:");                                          \
        fieldInfo.isProtected = std::string( #__VA_ARGS__ ) == "protected:";                        \
        fieldInfo.isPrivate = std::string( #__VA_ARGS__ ) == "private:";                            \
        result[fieldInfo.fieldName] = (std::move(fieldInfo));                                       \
    }                                                                                               \

//

#define IMPL_NOT_REQ_REFLECTION_FIELD_VALUE_INFO(type, valName, ...)                                \
    {                                                                                               \
        egt::IBaseComponent::FieldInfo fieldInfo;                                                   \
        fieldInfo.fieldName = #valName;                                                             \
        fieldInfo.fieldType = GetTypeName<type>();                                                  \
        fieldInfo.isRequired = false;                                                               \
        fieldInfo.isPublic =                                                                        \
                (std::string( #__VA_ARGS__ ) == "" ||                                               \
                std::string( #__VA_ARGS__ ) == "public:");                                          \
        fieldInfo.isProtected = std::string( #__VA_ARGS__ ) == "protected:";                        \
        fieldInfo.isPrivate = std::string( #__VA_ARGS__ ) == "private:";                            \
        result[fieldInfo.fieldName] = (std::move(fieldInfo));                                       \
    }                                                                                               \


#define ADD_COMPONENT_NAME_TO_ID_TO_MAP(compName, foo)      \
    {#compName, EComponentId::COMP_ID_##compName},          \

//

#define ADD_COMPONENT_ID_TO_NAME_TO_MAP(compName, foo)      \
    {EComponentId::COMP_ID_##compName, #compName},          \

//

///////////////////////////////////////////////////////////////////////////
#define COMP_FACTORY_HASH_CALC(compName, foo)                               \
    hashes.push_back(compName##Component::GetComponentTypeHashStatic());    \


///////////////////////////////////////////////////////////////////////////
#define COMP_DECLARE_HIDDEN_FUNCTIONS(valIterator, compName) \


///////////////////////////////////////////////////////////////////////////
#define COMP_IMPLEMENT_HIDDEN_FUNCTIONS(compName, foo) \

///////////////////////////////////////////////////////////////////////////
#define COMP_CONSTRUCTOR_VALUE_INIT(type, valName, ...)    \
    , m_##valName(type())       \
    , m_has_##valName(false)    \

///////////////////////////////////////////////////////////////////////////
#define COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(VAL_ITERATOR)                    \
    egt::IBaseComponent()                                                       \
    VAL_ITERATOR(COMP_CONSTRUCTOR_VALUE_INIT, COMP_CONSTRUCTOR_VALUE_INIT)      \

///////////////////////////////////////////////////////////////////////////
#define COMP_CLEAR_VALUE(type, valName, ...)    \
    Clear_##valName();                          \

///////////////////////////////////////////////////////////////////////////
#define COMP_CHECK_IS_EMPTY_VALUE(type, valName, ...)       \
    if (Has_##valName()) return false;                      \

///////////////////////////////////////////////////////////////////////////
#define COMP_CHECK_IS_EQUAL_VALUE(type, valName, ...)                               \
    if (this->Has_##valName() != myTypePtr->Has_##valName()) return false;          \
    if ((this->Has_##valName()) && (this->Get_##valName() != myTypePtr->Get_##valName()))   \
        return false;                                                               \

///////////////////////////////////////////////////////////////////////////
#define COMP_COPY_FROM_VALUE(type, valName, ...)                                    \
    if (myTypePtr->Has_##valName()) this->Set_##valName(myTypePtr->Get_##valName());\
    else this->Clear_##valName();                                                   \

#endif // COMPONENTMACROENGINE_H
