///////////////////////////////////////////////////////////////////////////
// Add include file and add new line with your component name in ther macro iterator
#undef CUSTOM_COMPONENTS_ITERATOR_CABINET
#define CUSTOM_COMPONENTS_ITERATOR_CABINET(CUSTOM_COMPONENT_MACRO)\
    CUSTOM_COMPONENT_MACRO(Screen, foo)\
    CUSTOM_COMPONENT_MACRO(Cabinet, foo)\
    CUSTOM_COMPONENT_MACRO(Series, foo)\
    CUSTOM_COMPONENT_MACRO(ConfigContainer, foo)\
// DO NOT DELETE THIS AND DO NOT PUT EMPTY LINE, THIS IS CREATE COMPONENT SCRIPT REGISTER MARKER
//
