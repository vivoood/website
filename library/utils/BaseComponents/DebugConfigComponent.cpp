/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */



// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "DebugConfigComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(DEBUGCONFIG_COMP_VALUES_ITERATOR_1470046558, DebugConfig, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool DebugConfigComponent::Load(const pugi::xml_node& xmlNode)
{
    DEBUGCONFIG_COMP_VALUES_ITERATOR_1470046558(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DebugConfigComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(DEBUGCONFIG_COMP_VALUES_ITERATOR_1470046558, DebugConfig);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DebugConfigComponent::Serialize(pugi::xml_node& node) const
{
    DEBUGCONFIG_COMP_VALUES_ITERATOR_1470046558(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DebugConfigComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(DEBUGCONFIG_COMP_VALUES_ITERATOR_1470046558, DebugConfig);
    return true;
}

///////////////////////////////////////////////////////////////////////////
DebugConfigComponent::DebugConfigComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(DEBUGCONFIG_COMP_VALUES_ITERATOR_1470046558)
{

}

///////////////////////////////////////////////////////////////////////////
DebugConfigComponent::~DebugConfigComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
DebugConfigComponent::MergeValidator(
    const DebugConfigComponent&,    // lowPriorityComp,
    const DebugConfigComponent&,    // highPriorityComp,
    DebugConfigComponent&)          // mergedComp)
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
std::unordered_map<std::string, std::string> DebugConfigComponent::GetAllEnabledCategories() const
{
  std::unordered_map<std::string, std::string> result;
  if (false == Has_logCategories())
  {
    return result;
  }
    for (const auto& categoryPair : Get_logCategories())
    {
 	  std::string logCategoryName = categoryPair.first;
 	  bool isEnabled = categoryPair.second.first;
 	  std::string rgbColor = categoryPair.second.second;
	  if (isEnabled)
	  {
	    result.emplace( std::make_pair( logCategoryName, rgbColor ) );
	  }
    }
    return result;
}
