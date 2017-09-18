/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#include "CabinetComponent.h"
#include "SeriesComponent.h"
#include "ScreenComponent.h"

#include <algorithm>

// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "ConfigContainerComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(CONFIGCONTAINER_COMP_VALUES_ITERATOR_1470139861, ConfigContainer, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool ConfigContainerComponent::Load(const pugi::xml_node& xmlNode)
{
    CONFIGCONTAINER_COMP_VALUES_ITERATOR_1470139861(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ConfigContainerComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(CONFIGCONTAINER_COMP_VALUES_ITERATOR_1470139861, ConfigContainer);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ConfigContainerComponent::Serialize(pugi::xml_node& node) const
{
    CONFIGCONTAINER_COMP_VALUES_ITERATOR_1470139861(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ConfigContainerComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(CONFIGCONTAINER_COMP_VALUES_ITERATOR_1470139861, ConfigContainer);
    return true;
}

///////////////////////////////////////////////////////////////////////////
ConfigContainerComponent::ConfigContainerComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(CONFIGCONTAINER_COMP_VALUES_ITERATOR_1470139861)
{

}

///////////////////////////////////////////////////////////////////////////
ConfigContainerComponent::~ConfigContainerComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
ConfigContainerComponent::MergeValidator(
    const ConfigContainerComponent&,    // lowPriorityComp,
    const ConfigContainerComponent&,    // highPriorityComp,
    ConfigContainerComponent&)          // mergedComp)
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool
ConfigContainerComponent::GetDefaultCabinetName(const std::string &seriesName, std::string &cabinetName)
{
    auto seriesContainer = GetContainer<SeriesComponent>("SeriesContainer");
    
    for (const auto &seriesComp : seriesContainer)
    {
        if (!seriesComp->Has_name())
            continue;
        
        if (seriesName != seriesComp->Get_name())
            continue;
        
        auto cabinetContainer = seriesComp->GetContainer<CabinetComponent>("Cabinets");
        
        const auto cabinetComp = cabinetContainer.begin();
        
        cabinetName = (*(*cabinetComp)->Get_names().begin());
        
        return true;
    }
    
    return false;
}

std::vector<std::shared_ptr<ScreenComponent>>
ConfigContainerComponent::GetScreensContainer(const std::string &seriesName, const std::string &cabinetName, int &displayCount)
{
    auto emptyResult = std::vector<std::shared_ptr<ScreenComponent>>();
    auto seriesContainer = GetContainer<SeriesComponent>("SeriesContainer");
    
    for (const auto &seriesComp : seriesContainer)
    {
        if (!seriesComp->Has_name())
            continue;
        
        if (seriesName != seriesComp->Get_name())
            continue;
        
        auto cabinetContainer = seriesComp->GetContainer<CabinetComponent>("Cabinets");
        
        for (const auto &cabinetComp : cabinetContainer)
        {
            auto end_it = cabinetComp->Get_names().end();
            if (end_it == std::find(cabinetComp->Get_names().begin(), end_it, cabinetName))
                continue;
            
            displayCount = cabinetComp->Get_displayCount();
            return cabinetComp->GetContainer<ScreenComponent>("Screens");
        }
    }
    
    
    return emptyResult;
}

