#ifndef BLOCKINGFUNCTIONCONNECTOR_H
#define BLOCKINGFUNCTIONCONNECTOR_H

#include <mutex>
#include <condition_variable>
#include <Messengers/Messenger.h>
#include "RemoteFunctionConnector.h"

namespace egt {

struct detachedFnCall
{
    detachedFnCall(std::condition_variable &c,
                    volatile bool &r,
                    oUniStream &res)
        : cv(c), repplied(r), resultStream(res) {}
    std::condition_variable &cv;
    volatile bool &repplied;
    oUniStream &resultStream;
};

class BlockingFunctionConnector: public RemoteFunctionConnector
{
public:
    BlockingFunctionConnector();

    virtual bool CallFunction(const std::string& funcName, oUniStream& argsStream, oUniStream& resultStream);
    virtual bool CallVoidFunction(const std::string& funcName, oUniStream& argsStream);
    //virtual bool IsConnected() const { return true; };
    void msgRcverCallFunc(std::vector<unsigned char>&& buff);
    void msgRcverReturnFunc(std::vector<unsigned char>& buff);
private:
    uint32_t msgRcverParseSeqN(std::vector<unsigned char>& buff);
    bool callDetachedFunction(std::vector<unsigned char>&, oUniStream&);

    std::map<const uint32_t, detachedFnCall *> msgWaitingMap;
    std::mutex m;
};

}

#endif // BLOCKINGFUNCTIONCONNECTOR_H
