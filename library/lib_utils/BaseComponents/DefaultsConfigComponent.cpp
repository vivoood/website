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
#include "DefaultsConfigComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(DEFAULTSCONFIG_COMP_VALUES_ITERATOR_1469539204, DefaultsConfig, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool DefaultsConfigComponent::Load(const pugi::xml_node& xmlNode)
{
    DEFAULTSCONFIG_COMP_VALUES_ITERATOR_1469539204(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DefaultsConfigComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(DEFAULTSCONFIG_COMP_VALUES_ITERATOR_1469539204, DefaultsConfig);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DefaultsConfigComponent::Serialize(pugi::xml_node& node) const
{
    DEFAULTSCONFIG_COMP_VALUES_ITERATOR_1469539204(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool DefaultsConfigComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(DEFAULTSCONFIG_COMP_VALUES_ITERATOR_1469539204, DefaultsConfig);
    return true;
}

///////////////////////////////////////////////////////////////////////////
DefaultsConfigComponent::DefaultsConfigComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(DEFAULTSCONFIG_COMP_VALUES_ITERATOR_1469539204)
{

}

///////////////////////////////////////////////////////////////////////////
DefaultsConfigComponent::~DefaultsConfigComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
DefaultsConfigComponent::MergeValidator(
    const DefaultsConfigComponent&,    // lowPriorityComp,
    const DefaultsConfigComponent&,    // highPriorityComp,
    DefaultsConfigComponent&)          // mergedComp)
{
    return true;
}
