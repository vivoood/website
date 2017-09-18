#include "SimpleFunctionConnector.h"

#include "../FunctionBinder/FunctionBinder.h"
#include <iostream>
using namespace egt;

///////////////////////////////////////////////////////////////////////////
bool SimpleFunctionConnector::FunctionExist(const std::string& funcName)
{
    bool res = m_binder->FunctionExist(funcName);
    return res;
}

///////////////////////////////////////////////////////////////////////////
bool SimpleFunctionConnector::CallFunction(const std::string& funcName, oUniStream& argsStream, oUniStream& resultStream)
{
    iUniStream argsIStream(argsStream);
    bool res = m_binder->RemoteCallFunction(funcName, argsIStream, resultStream);
    return res;
}

///////////////////////////////////////////////////////////////////////////
bool SimpleFunctionConnector::CallVoidFunction(const std::string& funcName, oUniStream& argsStream)
{
    iUniStream argsIStream(argsStream);
    oUniStream dummyResultStream;
    bool res = m_binder->RemoteCallFunction(funcName, argsIStream, dummyResultStream);
    return res;
}

///////////////////////////////////////////////////////////////////////////
void SimpleFunctionConnector::Connect(FunctionBinder& binderPtr)
{
    m_binder = &binderPtr;
}

void SimpleFunctionConnector::Disconnect()
{
    m_binder = nullptr;
}
