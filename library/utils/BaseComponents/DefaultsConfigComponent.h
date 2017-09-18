/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef __COMP_DEFAULTSCONFIG_1469539204_
#define __COMP_DEFAULTSCONFIG_1469539204_

#include <string>
#include <vector>

// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "Settings/Defines.h"
#include "Settings/Includes.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
namespace COMPONENT_FACTORY_NAMESPACE {
// Put your typedefs here:

typedef std::vector<std::string> DenomList;
  
///////////////////////////////////////////////////////////////////
#define DEFAULTSCONFIG_COMP_VALUES_ITERATOR_1469539204(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
	NOT_REQUIRED(bool,			bigWinDemo,)			\
	NOT_REQUIRED(bool,			showLoopInfo,)			\
	NOT_REQUIRED(std::string,		ipLogReport,)			\
	REQUIRED(DenomList,			denominations,)			\
	REQUIRED(DenomList,			tokenDenominations,)		\
	REQUIRED(DenomList,			billDenominations,)		\
	REQUIRED(std::vector<int>,		hoperMaxLimit,)			\
	REQUIRED(std::vector<int>,		autoPlayedGames,)		\
	REQUIRED(std::vector<int>,		localJackpotPercent,)		\
    
// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class DefaultsConfigComponent;
typedef std::shared_ptr<DefaultsConfigComponent> DefaultsConfigComponentPtr;

class DefaultsConfigComponent : public egt::IBaseComponent
{
	EGT_COMPONENT_COMMON_DECLARATIONS(DEFAULTSCONFIG_COMP_VALUES_ITERATOR_1469539204, DefaultsConfig)

public:

protected:


private:

};

}

#endif // __COMP_DEFAULTSCONFIG_1469539204_


