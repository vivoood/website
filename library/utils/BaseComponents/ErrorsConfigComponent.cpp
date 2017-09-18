/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#include <algorithm>

// Put your includes above this line
///////////////////////////////////////////////////////////////////
/// !!! DO NOT INCLUDE ANY FILES AFTER THIS LINE !!!
#include "ErrorsConfigComponent.h"
///////////////////////////////////////////////////////////////////////////
using namespace COMPONENT_FACTORY_NAMESPACE;
#include "System/push_warning_level.h"
#include "System/stop_unused_var_warning.h"
IMPLEMENT_COMPONENT_COMMON_METHODS(ERRORSCONFIG_COMP_VALUES_ITERATOR_1470222136, ErrorsConfig, FACTORY_NAMESPACE_STRING)
#include "System/pop_warning_level.h"
/// !!! DO NOT INCLUDE ANY FILES HERE !!!
///////////////////////////////////////////////////////////////////////////
bool ErrorsConfigComponent::Load(const pugi::xml_node& xmlNode)
{
    ERRORSCONFIG_COMP_VALUES_ITERATOR_1470222136(COMP_IMPLEMENT_REQ_LOADER, COMP_IMPLEMENT_NOT_REQ_LOADER);
    
    std::replace( m_clears.begin(), m_clears.end(), '^', ' ' );
    std::replace( m_description.begin(), m_description.end(), '^', ' ' );
    std::replace( m_solution.begin(), m_solution.end(), '^', ' ' );
    
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ErrorsConfigComponent::Load(egt::iUniStream& inputStream)
{
    COMP_IMPLEMENT_BIN_LOAD(ERRORSCONFIG_COMP_VALUES_ITERATOR_1470222136, ErrorsConfig);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ErrorsConfigComponent::Serialize(pugi::xml_node& node) const
{
    ERRORSCONFIG_COMP_VALUES_ITERATOR_1470222136(COMP_IMPLEMENT_REQ_WRITER, COMP_IMPLEMENT_NOT_REQ_WRITER);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ErrorsConfigComponent::Serialize(egt::oUniStream& outStream) const
{
    COMP_IMPLEMENT_BIN_SERIALIZE(ERRORSCONFIG_COMP_VALUES_ITERATOR_1470222136, ErrorsConfig);
    return true;
}

///////////////////////////////////////////////////////////////////////////
ErrorsConfigComponent::ErrorsConfigComponent()
    : COMP_IMPLEMENT_CONSTRUCTOR_VALUES_INIT(ERRORSCONFIG_COMP_VALUES_ITERATOR_1470222136)
{

}

///////////////////////////////////////////////////////////////////////////
ErrorsConfigComponent::~ErrorsConfigComponent()
{

}

///////////////////////////////////////////////////////////////////////////
bool
ErrorsConfigComponent::MergeValidator(
    const ErrorsConfigComponent&,    // lowPriorityComp,
    const ErrorsConfigComponent&,    // highPriorityComp,
    ErrorsConfigComponent&)          // mergedComp)
{
    return true;
}

/////////////////////////////////////////////////////////////////////////////
ErrorsConfigComponentPtr ErrorsConfigComponent::FindComponentByErrorCode ( std::string errorCode )
{
  
  std::vector<ErrorsConfigComponentPtr> container = GetContainer<ErrorsConfigComponent>("configs");
  
  for (ErrorsConfigComponentPtr comp : container)
  {
    if (comp->Get_codeId() == errorCode)
    {
      return comp;
    }
  }
  return nullptr;
}

/////////////////////////////////////////////////////////////////////////////
bool ErrorsConfigComponent::GetClears ( std::string errorCode, std::string& result )
{
  ErrorsConfigComponentPtr comp = FindComponentByErrorCode(errorCode);
  if (comp != nullptr && comp->Has_clears())
  {
    result =  comp->Get_clears();
    return true;
  }
  return false;
}

/////////////////////////////////////////////////////////////////////////////
bool ErrorsConfigComponent::GetDescription ( std::string errorCode, std::string& result )
{
    ErrorsConfigComponentPtr comp = FindComponentByErrorCode ( errorCode );
    if ( comp != nullptr && comp->Has_description() )
    {
        result =  comp->Get_description();
	return true;
    }
    return false;
}

/////////////////////////////////////////////////////////////////////////////
bool ErrorsConfigComponent::GetSolution ( std::string errorCode, std::string& result )
{
    ErrorsConfigComponentPtr comp = FindComponentByErrorCode ( errorCode );
    if ( comp != nullptr && comp->Has_solution() )
    {
        result = comp->Get_solution();
	return true;
    }
    return false;
}

