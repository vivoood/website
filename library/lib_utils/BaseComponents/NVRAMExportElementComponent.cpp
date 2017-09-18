/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */



#include <algorithm>	//TODO: it will be removed when removing std::replace( m_queryPath...) below


// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "NVRAMExportElementComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(NVRAMEXPORTELEMENT_COMP_VALUES_ITERATOR_1236, NVRAMExportElement, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool NVRAMExportElementComponent::Load(const pugi::xml_node& xmlNode)
{
    NVRAMEXPORTELEMENT_COMP_VALUES_ITERATOR_1236(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);

    //TODO: Here symbol ^ means <space>. Now it is replaced with <space> into cpp code. It will be fixed soon.
    std::replace( m_queryPath.begin(), m_queryPath.end(), '^', ' ' );

    return true;
}

///////////////////////////////////////////////////////////////////////////
bool NVRAMExportElementComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(NVRAMEXPORTELEMENT_COMP_VALUES_ITERATOR_1236, NVRAMExportElement);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool NVRAMExportElementComponent::Serialize(pugi::xml_node& node) const
{
    //TODO: Here symbol ^ means <space>. Now it is replaced with <space> into cpp code. It will be fixed soon.
//    std::replace( m_queryPath.begin(), m_queryPath.end(), ' ', '^' );

    NVRAMEXPORTELEMENT_COMP_VALUES_ITERATOR_1236(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);

    //TODO: Here symbol ^ means <space>. Now it is replaced with <space> into cpp code. It will be fixed soon.
//    std::replace( m_queryPath.begin(), m_queryPath.end(), '^', ' ' );
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool NVRAMExportElementComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(NVRAMEXPORTELEMENT_COMP_VALUES_ITERATOR_1236, NVRAMExportElement);
    return true;
}

///////////////////////////////////////////////////////////////////////////
NVRAMExportElementComponent::NVRAMExportElementComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(NVRAMEXPORTELEMENT_COMP_VALUES_ITERATOR_1236)
{

}

///////////////////////////////////////////////////////////////////////////
NVRAMExportElementComponent::~NVRAMExportElementComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
NVRAMExportElementComponent::MergeValidator(
    const NVRAMExportElementComponent&,    // lowPriorityComp,
    const NVRAMExportElementComponent&,    // highPriorityComp,
    NVRAMExportElementComponent&)          // mergedComp)
{
    return true;
}
