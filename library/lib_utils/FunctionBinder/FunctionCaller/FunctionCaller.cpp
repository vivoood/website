#include "FunctionCaller.h"
#include <iostream>
using namespace egt;

///////////////////////////////////////////////////////////////////////////
FunctionCaller::FunctionCaller()
    : m_isConnected(false)
    , m_connector(nullptr)
{

}

///////////////////////////////////////////////////////////////////////////
FunctionCaller::~FunctionCaller()
{

}

///////////////////////////////////////////////////////////////////////////
bool FunctionCaller::FunctionExist(const std::string& funcName)
{
    bool res = m_connector->FunctionExist(funcName);
    return res;
}

///////////////////////////////////////////////////////////////////////////
bool FunctionCaller::Connect( FunctionConnector& connectorPtr )
{
    m_connector = &connectorPtr;
    m_isConnected = true;
    return true;
}

///////////////////////////////////////////////////////////////////////////
void FunctionCaller::Disconnect()
{
    m_connector = nullptr;
    m_isConnected = false;
}
