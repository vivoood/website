#include "RemoteFunctionConnector.h"

#include "../FunctionBinder/FunctionBinder.h"
#include <iostream>
using namespace egt;

///////////////////////////////////////////////////////////////////////////
RemoteFunctionConnector::RemoteFunctionConnector():m_binder(nullptr)
{

}

///////////////////////////////////////////////////////////////////////////
bool RemoteFunctionConnector::FunctionExist(const std::string& funcName)
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool RemoteFunctionConnector::CallFunction(const std::string& funcName, oUniStream& argsStream, oUniStream& resultStream)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool RemoteFunctionConnector::CallVoidFunction(const std::string& funcName, oUniStream& argsStream)
{
    oUniStream buffStream;
    buffStream << funcName << argsStream;
    if (nullptr != m_sendBuff)
    {
        m_sendBuff(buffStream.GetBuffer());
    }
    else
    {
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
void RemoteFunctionConnector::BufferReceived(std::vector<unsigned char>&& buff)
{
    oUniStream resultStream;
    BufferReceived(std::move(buff), resultStream);
}

//////////////////////////////////////////////////////////////////////////
void RemoteFunctionConnector::BufferReceived(std::vector<unsigned char>&& buff, oUniStream& resultStream)
{
    iUniStream buffStream(std::move(buff)), argsStream;
    std::string name;

    buffStream >> name >> argsStream;
    bool res = m_binder->RemoteCallFunction(name, argsStream, resultStream);
    if (false == res)
    {

    }
}

///////////////////////////////////////////////////////////////////////////
void RemoteFunctionConnector::Connect(FunctionBinder& binderPtr)
{
    m_binder = &binderPtr;
}

void RemoteFunctionConnector::Disconnect()
{
    m_binder = nullptr;
}
