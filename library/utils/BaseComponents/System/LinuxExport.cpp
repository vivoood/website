#include "ComponentsFactory.h"
#include "../Settings/ComponentsIncludeList.h"

#define CONCAT(a,b) a##b
#define FACTORY_FUNC_NAME(funcName, nameSpace)  CONCAT(nameSpace, funcName)

//
// ComponentNamespace_CreateEmptyMgr(...)
extern "C"
void
FACTORY_FUNC_NAME(_CreateEmptyMgr, COMPONENT_FACTORY_NAMESPACE) (egt::ComponentMgrPtr& result, const std::string& mgrName)
{
    result = COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateEmptyMgr(mgrName);
}

//
// ComponentNamespace_CreateFromFile(...)
extern "C" void
FACTORY_FUNC_NAME(_CreateFromFile, COMPONENT_FACTORY_NAMESPACE) (egt::ComponentMgrPtr& result, const std::string& fileName, const std::string& mgrName)
{
    result = COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateMgrFromFile(fileName, mgrName);
}

//
// ComponentNamespace_CreateFromStream(...)
extern "C" void
FACTORY_FUNC_NAME(_CreateFromStream, COMPONENT_FACTORY_NAMESPACE) (egt::ComponentMgrPtr& result, egt::iUniStream& inpStream)
{
    result = COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateMgrFromStream(inpStream);
}

//
// ComponentNamespace_GetFactoryHash(...)
extern "C" void
FACTORY_FUNC_NAME(_GetFactoryHash, COMPONENT_FACTORY_NAMESPACE) (uint64_t& result)
{
    result = COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::GetFactoryHash();
}

//
// ComponentNamespace_AutoMerge(...)
extern "C" void
FACTORY_FUNC_NAME(_AutoMerge, COMPONENT_FACTORY_NAMESPACE) (egt::IBaseComponentPtr& result, const egt::IBaseComponentPtr& lowPriorityCompPtr, const egt::IBaseComponentPtr& highPriorityCompPtr)
{
    result = COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::AutoMerge(lowPriorityCompPtr, highPriorityCompPtr);
}

//
// ComponentNamespace_GetComponents(...)
extern "C" void
FACTORY_FUNC_NAME(_GetComponents, COMPONENT_FACTORY_NAMESPACE) (std::map<int, std::string>& result)
{
    for (auto p : COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::GetComponentsMap())
    {
        result[(int)p.first] = p.second;
    }
}

//
// ComponentNamespace_AddToExistingMgrInFile(...)
extern "C" bool
FACTORY_FUNC_NAME(_AddToExistingMgrInFile, COMPONENT_FACTORY_NAMESPACE) (const std::string& fileName, egt::ComponentMgrPtr newMgr)
{
    return egt::SerializeTools::AddToComponentMgr
            <COMPONENT_FACTORY_NAMESPACE::ComponentsFactory>(fileName, newMgr);
}

//
// ComponentNamespace_ReplaceExistingMgrInFile(...)
extern "C" bool
FACTORY_FUNC_NAME(_ReplaceExistingMgrInFile, COMPONENT_FACTORY_NAMESPACE) (const std::string& fileName, egt::ComponentMgrPtr newMgr)
{
    return egt::SerializeTools::ReplaceComponentMgr
            <COMPONENT_FACTORY_NAMESPACE::ComponentsFactory>(fileName, newMgr);
}

//
// ComponentNamespace_BeautifyComponentsXml(...)
extern "C" bool
FACTORY_FUNC_NAME(_BeautifyComponentsXml, COMPONENT_FACTORY_NAMESPACE) (const std::string& fileName)
{
    return egt::SerializeTools::BeautifyComponentsXml
            <COMPONENT_FACTORY_NAMESPACE::ComponentsFactory>(fileName);
}

//
// ComponentNamespace_CreateComponent(...)
extern "C" egt::IBaseComponentPtr
FACTORY_FUNC_NAME(_CreateComponent, COMPONENT_FACTORY_NAMESPACE) (const std::string& compName)
{
    return COMPONENT_FACTORY_NAMESPACE::ComponentsFactory::CreateComponent(compName);
}


//
// ComponentNamespace_MergeManagers(...)
extern "C" egt::ComponentMgrPtr
FACTORY_FUNC_NAME(_MergeManagers, COMPONENT_FACTORY_NAMESPACE) (egt::ComponentMgrPtr lowPriorityMgr, egt::ComponentMgrPtr highPriorityMgr)
{
    return egt::ComponentMgr::Merge(lowPriorityMgr, highPriorityMgr);
}
//
