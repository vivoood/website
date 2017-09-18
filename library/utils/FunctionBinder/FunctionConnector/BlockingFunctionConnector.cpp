#include <tuple>
#include <condition_variable>
#include "BlockingFunctionConnector.h"

const int timeout_ms = 1000;

using namespace egt;

BlockingFunctionConnector::BlockingFunctionConnector()
{
}

bool BlockingFunctionConnector::CallFunction(const std::string &funcName, oUniStream &argsStream, oUniStream &resultStream)
{
    bool ret;
    oUniStream buffStream;
    buffStream << funcName << argsStream;
    ret = callDetachedFunction(buffStream.GetBuffer(), resultStream);
    return ret;
}

bool BlockingFunctionConnector::CallVoidFunction(const std::string &funcName, oUniStream &argsStream)
{
    bool ret;
    oUniStream buffStream;
    oUniStream resultStream;
    buffStream << funcName << argsStream;
    ret = callDetachedFunction(buffStream.GetBuffer(), resultStream);
    return ret;
}

uint32_t BlockingFunctionConnector::msgRcverParseSeqN(std::vector<unsigned char> &buff)
{
    uint32_t msg_seq_num = 0;
    unsigned char *tmp_ptr = (unsigned char *)&msg_seq_num;

    if (buff.size() >= sizeof(msg_seq_num))
    {
        for (size_t i = 0; i < sizeof(msg_seq_num); i++, tmp_ptr++)
        {
            *tmp_ptr = buff[0];
            buff.erase(buff.begin());
        }
    }

    return msg_seq_num;
}

void BlockingFunctionConnector::msgRcverCallFunc(std::vector<unsigned char> &&buff)
{
    uint32_t seq_num = msgRcverParseSeqN(buff);
    oUniStream resultStream;
    BufferReceived(std::move(buff), resultStream);
    oUniStream streamPack;
    streamPack << resultStream;
    std::vector<unsigned char> reply;
    std::vector<unsigned char>&result = streamPack.GetBuffer();
    // write the msg sequence number in the payload
    unsigned char *tmp_ptr = (unsigned char *)&seq_num;
    for (size_t i = 0; i < sizeof(seq_num); i++, tmp_ptr++)
        reply.push_back(*tmp_ptr);

    for (size_t i = 0; i < result.size(); i++)
        reply.push_back(result[i]);

    m_sendBuff(reply);
}

void BlockingFunctionConnector::msgRcverReturnFunc(std::vector<unsigned char> &buff)
{
    uint32_t seq_num = msgRcverParseSeqN(buff);
    detachedFnCall *fnCall;
    std::unique_lock<std::mutex> lk(m);

    auto connIter = msgWaitingMap.find(seq_num);
    if (connIter != msgWaitingMap.end())
    {
        fnCall = connIter->second;
        msgWaitingMap.erase(connIter);
    }
    else
        return;

    lk.unlock();
    iUniStream iStreamPack(buff);
    iStreamPack >> fnCall->resultStream;
    fnCall->repplied = true;
    fnCall->cv.notify_one();
}

bool BlockingFunctionConnector::callDetachedFunction(std::vector<unsigned char>& buff, oUniStream &resultStream)
{
    static uint32_t seq_num = 0;
    std::condition_variable cv;
    volatile bool repplied = false;
    std::vector<unsigned char> send_buff;
    std::unique_lock<std::mutex> lk(m);

    uint32_t msg_seq_num = seq_num++;
    lk.unlock();

    // write the msg sequence number in the payload
    unsigned char *tmp_ptr = (unsigned char *)&msg_seq_num;
    for (size_t i = 0; i < sizeof(msg_seq_num); i++, tmp_ptr++)
        send_buff.push_back(*tmp_ptr);

    for (size_t i = 0; i < buff.size(); i++)
        send_buff.push_back(buff[i]);

    detachedFnCall fnCall(cv, repplied, resultStream);

    lk.lock();

    msgWaitingMap[msg_seq_num] = &fnCall;
    m_sendBuff(send_buff);

    std::cv_status ret = std::cv_status::no_timeout;

    while (ret == std::cv_status::no_timeout && repplied == false)
           ret = cv.wait_for(lk, std::chrono::milliseconds(timeout_ms));

    if (ret != std::cv_status::no_timeout)
    {
        auto connIter = msgWaitingMap.find(msg_seq_num);
        if (connIter != msgWaitingMap.end())
        {
            msgWaitingMap.erase(connIter);
        }
    }

    return (ret == std::cv_status::no_timeout);

}
