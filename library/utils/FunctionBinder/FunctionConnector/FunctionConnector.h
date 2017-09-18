#pragma once
#include <functional>
#include <string>

namespace egt {

class iUniStream;
class oUniStream;

class FunctionConnector
{

public:
    FunctionConnector(){};
    virtual ~FunctionConnector(){};


    virtual bool FunctionExist(const std::string& funcName) = 0;
    virtual bool CallFunction(const std::string& funcName, oUniStream& argsStream, oUniStream& resultStream) = 0;
    virtual bool CallVoidFunction(const std::string& funcName, oUniStream& argsStream) = 0;
    virtual bool IsConnected() const = 0;

protected:

private:
};

}
