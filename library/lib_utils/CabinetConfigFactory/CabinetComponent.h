/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef __COMP_CABINET_1470137711_
#define __COMP_CABINET_1470137711_

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
#define CABINET_COMP_VALUES_ITERATOR_1470137711(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName,            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray,             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
	REQUIRED(   int,                displayCount,)           \
	REQUIRED(   int,                maxScreenCount,)         \
	REQUIRED(   std::vector<std::string>,  names,)                 \


// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class CabinetComponent;
typedef std::shared_ptr<CabinetComponent> CabinetComponentPtr;

class CabinetComponent : public egt::IBaseComponent
{
	EGT_COMPONENT_COMMON_DECLARATIONS(CABINET_COMP_VALUES_ITERATOR_1470137711, Cabinet)

public:

protected:

private:

};

}

#endif // __COMP_CABINET_1470137711_
