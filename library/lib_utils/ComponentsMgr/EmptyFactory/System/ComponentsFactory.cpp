#include "ComponentsFactory.h"
#include "../Settings/ComponentsIncludeList.h"

///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;

CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(IMPLEMENT_COMPONENT_STREAM_OPERATORS)
CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(IMPLEMENT_COMPONENT_ID_GETTERS)

const std::map<std::string, COMPONENT_FACTORY_NAMESPACE::EComponentId> COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::s_componentsNameToIdMap =
{
    CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(ADD_COMPONENT_NAME_TO_ID_TO_MAP)
};

const std::map<COMPONENT_FACTORY_NAMESPACE::EComponentId, std::string> COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::s_componentsIdToNameMap =
{
    CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(ADD_COMPONENT_ID_TO_NAME_TO_MAP)
};

///////////////////////////////////////////////////////////////////////////
bool COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::Init()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
egt::IBaseComponentPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateComponent(const pugi::xml_node& inputData)
{
    std::string compTypeStr;
    if (false == egt::IBaseComponent::ReadType(inputData, compTypeStr))
    {
        return egt::IBaseComponentPtr();
    }

    auto iterator = s_componentsNameToIdMap.find( compTypeStr );
    if (iterator == s_componentsNameToIdMap.end())
    {
        return egt::IBaseComponentPtr(nullptr);
    }

    auto componentId = iterator->second;
    switch(componentId)
    {
        CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(IMPLEMENT_COMPONENT_LOADER)

        default:
        {
        }
        break;
    }

    return egt::IBaseComponentPtr(nullptr);
}

egt::IBaseComponentPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateComponent(egt::iUniStream& inputData)
{
    u_int32_t componentIntId;
    if (!(inputData >> componentIntId))
    {
        return egt::IBaseComponentPtr(nullptr);
    }
    EComponentId componentId = (EComponentId)componentIntId;

    switch(componentId)
    {
        CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(IMPLEMENT_COMPONENT_LOADER)

        default:
        {
        }
        break;
    }

    return egt::IBaseComponentPtr(nullptr);
}

///////////////////////////////////////////////////////////////////////////
egt::IBaseComponentPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateComponent(const std::string& name)
{
    auto iterator = s_componentsNameToIdMap.find( name );
    if (iterator == s_componentsNameToIdMap.end())
    {
        return egt::IBaseComponentPtr(nullptr);
    }

    auto componentId = iterator->second;
    switch(componentId)
    {
        CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(IMPLEMENT_COMPONENT_CREATOR)

        default:
        {
            COMP_LOG << "Trying to create unknown component : " << name;
        }
        break;
    }

    return egt::IBaseComponentPtr(nullptr);
}

///////////////////////////////////////////////////////////////////////////
egt::IBaseComponentPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::AutoMerge(const egt::IBaseComponentPtr& lowPriorityCompPtr, const egt::IBaseComponentPtr& highPriorityCompPtr)
{
    if (lowPriorityCompPtr->GetComponentId() != highPriorityCompPtr->GetComponentId())
    {
        COMP_LOG << "Merging different components: "  << lowPriorityCompPtr->GetComponentName() << ", " << highPriorityCompPtr->GetComponentName();
        COMP_ASSERT("Merging different components");
        return nullptr;
    }
    EComponentId compId = EComponentId(lowPriorityCompPtr->GetComponentId());

    switch(compId)
    {
        CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(IMPLEMENT_COMPONENT_MERGER)

        default:
        {
        }
        break;
    }
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////
u_int64_t
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::GetFactoryHash()
{
    static u_int64_t hash = 0;
    static bool hashReady = false;

    if (false == hashReady)
    {
        std::vector<u_int64_t> hashes;
        CUSTOM_COMPONENTS_ITERATOR_EMPTYLOCK(COMP_FACTORY_HASH_CALC)
        hashes.push_back(egt::HashConstructor::ConstructHash(FACTORY_NAMESPACE_STRING));
        hash = egt::HashConstructor::ConstructHash(hashes);
        hashReady = true;
    }

    return hash;
}

///////////////////////////////////////////////////////////////////////////
const std::map<EComponentId, std::string>&
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::GetComponentsMap()
{
    return s_componentsIdToNameMap;
}

///////////////////////////////////////////////////////////////////////////
egt::ComponentMgrPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateEmptyMgr(const std::string& mgrName)
{
    return egt::ComponentMgr::CreateEmptyMgr<COMPONENT_FACTORY_NAMESPACE::ComponentsFactory>(mgrName);
}

///////////////////////////////////////////////////////////////////////////
egt::ComponentMgrPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateMgrFromFile(const std::string& fileName, const std::string& mgrName)
{
    return egt::ComponentMgr::CreateFromFile<COMPONENT_FACTORY_NAMESPACE::ComponentsFactory>(fileName, mgrName);
}

///////////////////////////////////////////////////////////////////////////
egt::ComponentMgrPtr
COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateMgrFromStream(egt::iUniStream& inpStream)
{
    return egt::ComponentMgr::CreateFromStream<COMPONENT_FACTORY_NAMESPACE::ComponentsFactory>(inpStream);
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

