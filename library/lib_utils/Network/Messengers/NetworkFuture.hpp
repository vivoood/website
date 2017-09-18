
namespace egt
{


///////////////////////////////////////////////////////////////////////

template<typename MsgType>
NetworkFuture<MsgType>::NetworkFuture(Locker)
    : NetworkFuture<MsgType>()
{}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
typename NetworkFuture<MsgType>::WaitResult NetworkFuture<MsgType>::WaitForReply(Duration timeout)
{
    auto waitUntil = std::chrono::system_clock::now() + timeout;
    while(m_isReady == false && std::chrono::system_clock::now() < waitUntil)
    {
        auto timeoutLeft = std::chrono::duration_cast<Duration>(waitUntil - std::chrono::system_clock::now());
        _waitForReply(timeoutLeft);
    }
    return m_waitResult;
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
typename NetworkFuture<MsgType>::WaitResult NetworkFuture<MsgType>::BlockForReply()
{
    while(m_isReady == false)
    {
        _waitForReply(Duration(-1));
    }
    return m_waitResult;
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
typename NetworkFuture<MsgType>::WaitResult NetworkFuture<MsgType>::CheckForReply()
{
    _waitForReply(Duration(0));
    return m_waitResult;
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
MsgType NetworkFuture<MsgType>::GetMsg()
{
    return std::move(m_msg);
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
void NetworkFuture<MsgType>::_waitForReply(Duration timeout)
{
    if (m_isReady)
    {
        return;
    }
    if (m_waitHandler != nullptr)
    {
        m_waitHandler(timeout);
    }
    else
    {
        m_isReady = true;
        m_waitResult = WaitResult::Error;
    }
}

}
