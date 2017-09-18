/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef _COMPFACTORY_1471274397
#define _COMPFACTORY_1471274397

#include "../Settings/Includes.h"
#include "../Settings/Defines.h"
#include "../Settings/ComponentsList.h"
///////////////////////////////////
#include <memory>
#include <map>
#include <string>
///////////////////////////////////
//

//
///////////////////////////////////
namespace pugi
{
    class xml_node;
}
namespace egt
{
    class iUniStream;
}


namespace COMPONENT_FACTORY_NAMESPACE {

enum class EComponentId
{
    CUSTOM_COMPONENTS_ITERATOR_BASE_COMPS(IMPLEMENT_COMPONENTS_ENUM)
};

class ComponentsFactory
{

public:
    static bool Init();
    static egt::IBaseComponentPtr CreateComponent(const pugi::xml_node& inputData);
    static egt::IBaseComponentPtr CreateComponent(egt::iUniStream& inputData);
    static egt::IBaseComponentPtr CreateComponent(const std::string& name);

    static egt::ComponentMgrPtr CreateEmptyMgr(const std::string& mgrName);
    static egt::ComponentMgrPtr CreateMgrFromFile(const std::string& fileName, const std::string& mgrName);
    static egt::ComponentMgrPtr CreateMgrFromStream(egt::iUniStream& inpStream);

    static u_int64_t GetFactoryHash();

    static egt::IBaseComponentPtr AutoMerge(const egt::IBaseComponentPtr& lowPriorityCompPtr, const egt::IBaseComponentPtr& highPriorityCompPtr);
    static const std::map<EComponentId, std::string>& GetComponentsMap();
private:
    ComponentsFactory();

    static  const std::map<std::string, EComponentId> s_componentsNameToIdMap;
    static  const std::map<EComponentId, std::string> s_componentsIdToNameMap;
};
//
} // namespace egt

#endif // _COMPFACTORY_1471274397
