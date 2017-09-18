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
#include "NVRAMImportExportComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(NVRAMIMPORTEXPORT_COMP_VALUES_ITERATOR_1237, NVRAMImportExport, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool NVRAMImportExportComponent::Load(const pugi::xml_node& xmlNode)
{
    NVRAMIMPORTEXPORT_COMP_VALUES_ITERATOR_1237(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool NVRAMImportExportComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(NVRAMIMPORTEXPORT_COMP_VALUES_ITERATOR_1237, NVRAMImportExport);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool NVRAMImportExportComponent::Serialize(pugi::xml_node& node) const
{
    NVRAMIMPORTEXPORT_COMP_VALUES_ITERATOR_1237(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool NVRAMImportExportComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(NVRAMIMPORTEXPORT_COMP_VALUES_ITERATOR_1237, NVRAMImportExport);
    return true;
}

///////////////////////////////////////////////////////////////////////////
NVRAMImportExportComponent::NVRAMImportExportComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(NVRAMIMPORTEXPORT_COMP_VALUES_ITERATOR_1237)
{

}

///////////////////////////////////////////////////////////////////////////
NVRAMImportExportComponent::~NVRAMImportExportComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
NVRAMImportExportComponent::MergeValidator(
    const NVRAMImportExportComponent&,    // lowPriorityComp,
    const NVRAMImportExportComponent&,    // highPriorityComp,
    NVRAMImportExportComponent&)          // mergedComp)
{
    return true;
}
