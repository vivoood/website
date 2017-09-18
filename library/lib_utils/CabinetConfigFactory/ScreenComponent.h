/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef __COMP_SCREEN_1470137705_
#define __COMP_SCREEN_1470137705_

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
#define SCREEN_COMP_VALUES_ITERATOR_1470137705(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName,            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray,             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
	REQUIRED(   std::string, id,              )        \
	REQUIRED(   int,         posX,            )        \
	REQUIRED(   int,         posY,            )        \
	REQUIRED(   int,         width,           )        \
	REQUIRED(   int,         height,          )        \
	REQUIRED(   int,         FBOWidth,        )        \
	REQUIRED(   int,         FBOHeight,       )        \

// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class ScreenComponent;
typedef std::shared_ptr<ScreenComponent> ScreenComponentPtr;

class ScreenComponent : public egt::IBaseComponent
{
	EGT_COMPONENT_COMMON_DECLARATIONS(SCREEN_COMP_VALUES_ITERATOR_1470137705, Screen)

public:

protected:

private:

};

}

#endif // __COMP_SCREEN_1470137705_
