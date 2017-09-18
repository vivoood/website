namespace egt
{

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
MsgType& NetworkPromise<MsgType>::GetRequest()
{
    return m_msg;
}

///////////////////////////////////////////////////////////////////////
template<typename MsgType>
typename NetworkPromise<MsgType>::SendResult NetworkPromise<MsgType>::Reply(MsgType& msg)
{
    auto connection = m_connection.lock();
    if (nullptr == connection)
    {
        return SendResult::Error;
    }
    if (m_replyHandler == nullptr)
    {
        return SendResult::Error;
    }

    return m_replyHandler(connection, std::move(msg));
}

}
