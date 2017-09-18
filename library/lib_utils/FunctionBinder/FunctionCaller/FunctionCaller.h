#pragma once
#include "../../UniStream/UniStream.h"

#include <functional>
#include <string>
#include <map>
#include <memory>
#include "../FunctionConnector/FunctionConnector.h"
#include "../FunctionCallErrors.h"

namespace egt {
class FunctionCaller
{
public:
    using Error = FunctionCallError;

    FunctionCaller();
    virtual ~FunctionCaller();

    bool Connect( FunctionConnector& connectorPtr );
    void Disconnect();

    bool FunctionExist(const std::string& funcName);
    bool IsConnected() const { return m_isConnected; };

    template<typename ResultType, typename ... ArgsTypes>
    FunctionCallResult<ResultType> CallFunction(const std::string& funcName, ArgsTypes ... args);

    template<typename ... ArgsTypes>
    FunctionCallResult<void> CallVoidFunction(const std::string& funcName, ArgsTypes ... args);

protected:

private:
    bool m_isConnected;
    FunctionConnector* m_connector;
};

#include "FunctionCaller.hpp"

}
