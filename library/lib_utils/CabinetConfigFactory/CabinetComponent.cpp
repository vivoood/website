/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#include <algorithm>


// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "CabinetComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(CABINET_COMP_VALUES_ITERATOR_1470137711, Cabinet, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool CabinetComponent::Load(const pugi::xml_node& xmlNode)
{
    CABINET_COMP_VALUES_ITERATOR_1470137711(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    
    if (Has_names())
    {
        for (auto& name : m_names )
        {
            //TODO: Here symbol ^ means <space>. Now it is replaced with <space> into cpp code. It will be fixed soon.
            std::replace( name.begin(), name.end(), '^', ' ' );
        }
    }
    
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool CabinetComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(CABINET_COMP_VALUES_ITERATOR_1470137711, Cabinet);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool CabinetComponent::Serialize(pugi::xml_node& node) const
{
    CABINET_COMP_VALUES_ITERATOR_1470137711(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool CabinetComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(CABINET_COMP_VALUES_ITERATOR_1470137711, Cabinet);
    return true;
}

///////////////////////////////////////////////////////////////////////////
CabinetComponent::CabinetComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(CABINET_COMP_VALUES_ITERATOR_1470137711)
{

}

///////////////////////////////////////////////////////////////////////////
CabinetComponent::~CabinetComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
CabinetComponent::MergeValidator(
    const CabinetComponent&,    // lowPriorityComp,
    const CabinetComponent&,    // highPriorityComp,
    CabinetComponent&)          // mergedComp)
{
    return true;
}
