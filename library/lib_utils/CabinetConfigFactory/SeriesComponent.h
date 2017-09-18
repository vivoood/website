/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef __COMP_SERIES_1470137778_
#define __COMP_SERIES_1470137778_

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
#define SERIES_COMP_VALUES_ITERATOR_1470137778(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName,            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray,             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
	REQUIRED(  std::string,        name,)                \
    
    
// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class SeriesComponent;
typedef std::shared_ptr<SeriesComponent> SeriesComponentPtr;

class SeriesComponent : public egt::IBaseComponent
{
	EGT_COMPONENT_COMMON_DECLARATIONS(SERIES_COMP_VALUES_ITERATOR_1470137778, Series)

public:

protected:

private:

};

}

#endif // __COMP_SERIES_1470137778_
