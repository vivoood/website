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
#include "ScreenComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(SCREEN_COMP_VALUES_ITERATOR_1470137705, Screen, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool ScreenComponent::Load(const pugi::xml_node& xmlNode)
{
    SCREEN_COMP_VALUES_ITERATOR_1470137705(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ScreenComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(SCREEN_COMP_VALUES_ITERATOR_1470137705, Screen);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ScreenComponent::Serialize(pugi::xml_node& node) const
{
    SCREEN_COMP_VALUES_ITERATOR_1470137705(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ScreenComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(SCREEN_COMP_VALUES_ITERATOR_1470137705, Screen);
    return true;
}

///////////////////////////////////////////////////////////////////////////
ScreenComponent::ScreenComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(SCREEN_COMP_VALUES_ITERATOR_1470137705)
{

}

///////////////////////////////////////////////////////////////////////////
ScreenComponent::~ScreenComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
ScreenComponent::MergeValidator(
    const ScreenComponent&,    // lowPriorityComp,
    const ScreenComponent&,    // highPriorityComp,
    ScreenComponent&)          // mergedComp)
{
    return true;
}
