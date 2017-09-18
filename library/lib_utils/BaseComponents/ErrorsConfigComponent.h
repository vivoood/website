/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef __COMP_ERRORSCONFIG_1470222136_
#define __COMP_ERRORSCONFIG_1470222136_

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
#define ERRORSCONFIG_COMP_VALUES_ITERATOR_1470222136(REQUIRED, NOT_REQUIRED)       \
    /*  USAGE:                                                      */      \
    /*  NOT_REQUIRED(   int,                valueName            )  */      \
    /*  NOT_REQUIRED(   std::vector<int>,   intArray             )  */      \
    /*  REQUIRED(       std::string,        someString, private: )  */      \
    /*                                                              */      \
    NOT_REQUIRED(int,			logErrorMask,)		\
    REQUIRED(std::string, 		codeId,)		\
    NOT_REQUIRED(std::string,		description,)		\
    NOT_REQUIRED(std::string,		solution,)		\
    NOT_REQUIRED(std::string,		clears,)		\
    

    
// Describe component values above, do not leave empty lines and terminate your lines with line-continuation character'\'
///////////////////////////////////////////////////////////////////
///
class ErrorsConfigComponent;
typedef std::shared_ptr<ErrorsConfigComponent> ErrorsConfigComponentPtr;

class ErrorsConfigComponent : public egt::IBaseComponent
{
	EGT_COMPONENT_COMMON_DECLARATIONS(ERRORSCONFIG_COMP_VALUES_ITERATOR_1470222136, ErrorsConfig)

public:
  
  bool GetDescription(std::string errorCode, std::string& result)  ;
  bool GetSolution(std::string errorCode, std::string& result ) ;
  bool GetClears(std::string errorCode, std::string& result ) ;
  
  
  
protected:

private:
  
  ErrorsConfigComponentPtr FindComponentByErrorCode(std::string errorCode) ;

};

}

#endif // __COMP_ERRORSCONFIG_1470222136_
