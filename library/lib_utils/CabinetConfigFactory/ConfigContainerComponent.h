/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef __COMP_CONFIGCONTAINER_1470139861_
#define __COMP_CONFIGCONTAINER_1470139861_

#include <string>


// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "Settings/Defines.h"
#include "Settings/Includes.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
namespace COMPONENT_FACTORY_NAMESPACE {
// Put your typedefs here:

class ScreenComponent;
    
///////////////////////////////////////////////////////////////////
#define CONFIGCONTAINER_COMP_VALUES_ITERATOR_1470139861(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName,            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray,             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \

    
// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class ConfigContainerComponent;
typedef std::shared_ptr<ConfigContainerComponent> ConfigContainerComponentPtr;

class ConfigContainerComponent : public egt::IBaseComponent
{
	EGT_COMPONENT_COMMON_DECLARATIONS(CONFIGCONTAINER_COMP_VALUES_ITERATOR_1470139861, ConfigContainer)

public:
    bool GetDefaultCabinetName(const std::string &seriesName, std::string &cabinetName);
    std::vector<std::shared_ptr<ScreenComponent>> GetScreensContainer(const std::string &seriesName, const std::string &cabinetName, int &displayCount);
protected:

private:

};

}

#endif // __COMP_CONFIGCONTAINER_1470139861_
