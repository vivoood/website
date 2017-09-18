#pragma once
#include "../../UniStream/UniStream.h"
#include "FunctionConnector.h"
#include <functional>
#include <string>
#include <memory>

namespace egt {

class FunctionBinder;

class SimpleFunctionConnector : public FunctionConnector
{

public:

    SimpleFunctionConnector();
    void Connect(FunctionBinder& binderPtr);
    void Disconnect();

    virtual bool FunctionExist(const std::string& funcName);
    virtual bool CallFunction(const std::string& funcName, oUniStream& argsStream, oUniStream& resultStream);
    virtual bool CallVoidFunction(const std::string& funcName, oUniStream& argsStream);
    virtual bool IsConnected() const { return (m_binder != nullptr); };
protected:

private:
    FunctionBinder* m_binder;
};

}
