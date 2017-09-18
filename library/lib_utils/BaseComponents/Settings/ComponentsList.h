///////////////////////////////////////////////////////////////////////////
// Add include file and add new line with your component name in ther macro iterator
#undef CUSTOM_COMPONENTS_ITERATOR_BASE_COMPS
#define CUSTOM_COMPONENTS_ITERATOR_BASE_COMPS(CUSTOM_COMPONENT_MACRO)\
    CUSTOM_COMPONENT_MACRO(NVRAMImportExport, foo)\
    CUSTOM_COMPONENT_MACRO(NVRAMExportElement, foo)\
    CUSTOM_COMPONENT_MACRO(DefaultsConfig, foo)\
    CUSTOM_COMPONENT_MACRO(DebugConfig, foo)\
    CUSTOM_COMPONENT_MACRO(ErrorsConfig, foo)\
// DO NOT DELETE THIS AND DO NOT PUT EMPTY LINE, THIS IS CREATE COMPONENT SCRIPT REGISTER MARKER
//
