/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */


#ifndef NVRAMEXPORTELEMENT_COMP_V146738232323
#define NVRAMEXPORTELEMENT_COMP_V146738232323

#include <string>


// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "Settings/Defines.h"
#include "Settings/Includes.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
namespace COMPONENT_FACTORY_NAMESPACE {
// Put your typedefs here:

//{
//	{ParentTagName {{attribute1 value1} {attribute2 value2}}}
//	{NextParentTagName {{attributeA1 valueA1} {attributeA2 valueA2}}}
//}

typedef std::map< std::string, std::string > AttributesMap;

typedef std::pair< std::string, AttributesMap > ParentPair;
typedef std::vector< ParentPair > ParentsVector;

typedef std::pair< std::string, AttributesMap > ChildPair;
typedef std::vector< ChildPair > ChildrenVector;

///////////////////////////////////////////////////////////////////
#define NVRAMEXPORTELEMENT_COMP_VALUES_ITERATOR_1236(REQUIRED, NOT_REQUIRED)                   \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName,            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray,             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
    REQUIRED(       std::string,        queryPath,   )   \
    NOT_REQUIRED(   std::string,        tagName,     )   \
    NOT_REQUIRED(   AttributesMap,      attributes,  )   \
    NOT_REQUIRED(   ParentsVector,      xmlParents,  )   \
    NOT_REQUIRED(   ChildrenVector,     xmlChildren, )   \


// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class NVRAMExportElementComponent;
typedef std::shared_ptr<NVRAMExportElementComponent> NVRAMExportElementComponentPtr;

class NVRAMExportElementComponent : public egt::IBaseComponent
{
    EGT_COMPONENT_COMMON_DECLARATIONS(NVRAMEXPORTELEMENT_COMP_VALUES_ITERATOR_1236, NVRAMExportElement)

public:

protected:

private:

};

}

#endif // NVRAMEXPORTELEMENT_COMP_V146738232323
