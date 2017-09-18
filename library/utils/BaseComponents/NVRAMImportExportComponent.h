/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */


#ifndef NVRAMIMPORTEXPORT_COMP_V146738232323
#define NVRAMIMPORTEXPORT_COMP_V146738232323

#include <string>


// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "Settings/Defines.h"
#include "Settings/Includes.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
namespace COMPONENT_FACTORY_NAMESPACE {
// Put your typedefs here:


///////////////////////////////////////////////////////////////////
#define NVRAMIMPORTEXPORT_COMP_VALUES_ITERATOR_1237(REQUIRED, NOT_REQUIRED)                   \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName,            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray,             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
		REQUIRED( std::string, mainXMLPath,) \


// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class NVRAMImportExportComponent;
typedef std::shared_ptr<NVRAMImportExportComponent> NVRAMImportExportComponentPtr;

class NVRAMImportExportComponent : public egt::IBaseComponent
{
    EGT_COMPONENT_COMMON_DECLARATIONS(NVRAMIMPORTEXPORT_COMP_VALUES_ITERATOR_1237, NVRAMImportExport)

public:

protected:

private:

};

}

#endif // NVRAMIMPORTEXPORT_COMP_V146738232323
