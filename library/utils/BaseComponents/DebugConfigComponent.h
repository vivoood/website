/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef __COMP_DEBUGCONFIG_1470046558_
#define __COMP_DEBUGCONFIG_1470046558_

#include <string>
#include <utility> 
#include <unordered_map>
// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "Settings/Defines.h"
#include "Settings/Includes.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
namespace COMPONENT_FACTORY_NAMESPACE {
// Put your typedefs here:

typedef std::pair<std::string, int> FileLogger;

typedef std::pair<bool, std::string> LogCategory;
typedef std::map<std::string, LogCategory> LogCategoriesMap;


///////////////////////////////////////////////////////////////////
#define DEBUGCONFIG_COMP_VALUES_ITERATOR_1470046558(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName,            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray,             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
	REQUIRED(bool,			debugEnabled,)		\
	REQUIRED(FileLogger,		fileToLog,)		\
	REQUIRED(LogCategoriesMap,		logCategories,)		\
	REQUIRED(std::string,		netLoggerProtocol,)	\
	REQUIRED(std::string,		netLoggerHost,)		\
	REQUIRED(std::string,		netLoggerPort,)		\

    
// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class DebugConfigComponent;
typedef std::shared_ptr<DebugConfigComponent> DebugConfigComponentPtr;

class DebugConfigComponent : public egt::IBaseComponent
{
	EGT_COMPONENT_COMMON_DECLARATIONS(DEBUGCONFIG_COMP_VALUES_ITERATOR_1470046558, DebugConfig)

public:
  std::unordered_map<std::string, std::string> GetAllEnabledCategories() const;
protected:

private:

};

}

#endif // __COMP_DEBUGCONFIG_1470046558_
