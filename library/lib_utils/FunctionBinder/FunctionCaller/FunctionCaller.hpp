


///////////////////////////////////////////////////////////////////////////
template<typename ResultType, typename ... ArgsTypes>
FunctionCallResult<ResultType>
FunctionCaller::CallFunction(const std::string& funcName, ArgsTypes ... args)
{
    if (false == m_connector->IsConnected())
    {
        throw "Disconnected connector usage.";
    }
    oUniStream argsStream, resStream;
    argsStream.Serialize(args ...);

    Error err = m_connector->CallFunction(funcName, argsStream, resStream) ? Error::NoError : Error::Unknown;
    iUniStream resInpStream(resStream);
    ResultType res;
    resInpStream >> res;

    return FunctionCallResult<ResultType>(err, std::move(res));
}

///////////////////////////////////////////////////////////////////////////
template<typename ... ArgsTypes>
FunctionCallResult<void>
FunctionCaller::CallVoidFunction(const std::string& funcName, ArgsTypes ... args)
{
    if (false == m_connector->IsConnected())
    {
        throw "Disconnected connector usage.";
    }
    oUniStream argsStream;
    argsStream.Serialize(args ...);

    Error err = m_connector->CallVoidFunction(funcName, argsStream) ? Error::NoError : Error::Unknown;
    return FunctionCallResult<void>(err);
}
