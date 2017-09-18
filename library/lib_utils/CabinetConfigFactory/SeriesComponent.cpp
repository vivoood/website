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
#include "SeriesComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(SERIES_COMP_VALUES_ITERATOR_1470137778, Series, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool SeriesComponent::Load(const pugi::xml_node& xmlNode)
{
    SERIES_COMP_VALUES_ITERATOR_1470137778(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool SeriesComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(SERIES_COMP_VALUES_ITERATOR_1470137778, Series);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool SeriesComponent::Serialize(pugi::xml_node& node) const
{
    SERIES_COMP_VALUES_ITERATOR_1470137778(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool SeriesComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(SERIES_COMP_VALUES_ITERATOR_1470137778, Series);
    return true;
}

///////////////////////////////////////////////////////////////////////////
SeriesComponent::SeriesComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(SERIES_COMP_VALUES_ITERATOR_1470137778)
{

}

///////////////////////////////////////////////////////////////////////////
SeriesComponent::~SeriesComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
SeriesComponent::MergeValidator(
    const SeriesComponent&,    // lowPriorityComp,
    const SeriesComponent&,    // highPriorityComp,
    SeriesComponent&)          // mergedComp)
{
    return true;
}
