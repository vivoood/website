#pragma once
#include "../../UniStream/UniStream.h"
#include "FunctionConnector.h"
#include <functional>
#include <string>
#include <memory>
#include <functional>

namespace egt {

class FunctionBinder;

class RemoteFunctionConnector : public FunctionConnector
{
public:
	using SendBufferFuncType = std::function<void(std::vector<unsigned char>&)>;
	
    RemoteFunctionConnector();
    void Connect(FunctionBinder& binderPtr);
    void Disconnect();

    virtual bool FunctionExist(const std::string& funcName);
    virtual bool CallFunction(const std::string& funcName, oUniStream& argsStream, oUniStream& resultStream);
    virtual bool CallVoidFunction(const std::string& funcName, oUniStream& argsStream);
    virtual bool IsConnected() const { return true; };

    void BufferReceived(std::vector<unsigned char>&& buff);
    void BufferReceived(std::vector<unsigned char>&& buff, oUniStream& resultStream);

    void SetSendBuffFunction(SendBufferFuncType sendBuff) { m_sendBuff = sendBuff; };
protected:
    SendBufferFuncType m_sendBuff;

private:
    FunctionBinder* m_binder;
};

}
