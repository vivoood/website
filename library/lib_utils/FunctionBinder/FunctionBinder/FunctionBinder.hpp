

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ... ArgsTypes>
FunctionBinder::SignalHandlerInfo FunctionBinder::ConnectSignal( const std::string& signalName,
                                            InstanceType& instance,
                                            void(InstanceType::*func)(ArgsTypes ... args),
                                            uint32_t priority)
{
    auto& signalContainer = GetSignalContainer(signalName);
    SignalHandlerInfo signalInfo;
    signalInfo.handlerId = GetFreeSignalHandlerId();
    signalInfo.functor = CreateFunctor(&instance, func, true);
    signalInfo.priority = priority;
    signalInfo.signalName = signalName;
    signalInfo.disabled = false;
    signalInfo.executeOnce = false;
    BindableObject& bindableObj = dynamic_cast<BindableObject&>(instance);
    signalInfo.isAliveMarker = bindableObj.GetIsAliveMarker();

    AddInSignalContainer(signalContainer, signalInfo);
    return signalInfo;
}



template<typename InstanceType, typename ... ArgsTypes>
FunctionBinder::SignalHandlerInfo FunctionBinder::ConnectStaticSignal(   const std::string& signalName,
                            InstanceType& instance,
                            std::function<void(ArgsTypes ... args)> func,
                            uint32_t priority)
{
    auto& signalContainer = GetSignalContainer(signalName);
    SignalHandlerInfo signalInfo;
    signalInfo.handlerId = GetFreeSignalHandlerId();
    signalInfo.functor = CreateStaticLambdaFunctor(func, true);
    signalInfo.priority = priority;
    signalInfo.signalName = signalName;
    signalInfo.disabled = false;
    signalInfo.executeOnce = false;
    BindableObject& bindableObj = dynamic_cast<BindableObject&>(instance);
    signalInfo.isAliveMarker = bindableObj.GetIsAliveMarker();

    AddInSignalContainer(signalContainer, signalInfo);
    return signalInfo;
}




///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType, typename ... ArgsTypes>
bool FunctionBinder::Register(const std::string& funcName, InstanceType& instance, ResultType (InstanceType::*func)(ArgsTypes ... args))
{
    if (m_functions.find(funcName) != m_functions.end())
    {
        return false;
    }
    m_functions[funcName] = CreateFunctor(&instance, func);
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<typename RetType, typename ... ArgsTypes>
bool FunctionBinder::RegisterStatic(const std::string& funcName, RetType(*func)(ArgsTypes ... args))
{
    if (m_functions.find(funcName) != m_functions.end())
    {
        return false;
    }
    m_functions[funcName] = CreateStaticFunctor(func);
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<typename ResultType, typename ... ArgsTypes>
ResultType
FunctionBinder::CallFunction(const std::string& funcName, ArgsTypes ... args)
{
    oUniStream argsStream, resStream;
    argsStream.Serialize(args ...);
    iUniStream iArgs(argsStream);
    RemoteCallFunction(funcName, iArgs, resStream);
    iUniStream resInpStream(resStream);
    ResultType res;
    resInpStream >> res;
    return res;
}

///////////////////////////////////////////////////////////////////////////
template<typename ... ArgsTypes>
void
FunctionBinder::CallVoidFunction(const std::string& funcName, ArgsTypes ... args)
{
    oUniStream argsStream, resStream;
    argsStream.Serialize(args ...);
    iUniStream iArgs(argsStream);
    RemoteCallFunction(funcName, iArgs, resStream);
}

///////////////////////////////////////////////////////////////////////////
template<typename ... ArgsTypes>
void FunctionBinder::DispatchSignal(const std::string& signalName, ArgsTypes ... args)
{
    if (m_mainThreadId != std::this_thread::get_id())
    {
        const unsigned uNumOfBacktraces = 50;
        eCDebug(LOG_CATEGORY_BACKTRACE) << "dispatch miltithreading ... FunctionBinder::DispatchSignal\n" << egt_debug::bt( uNumOfBacktraces );
        throw "FunctionBinder::DispatchSignal";
    }

    m_signalDispatcherDepth++;
    OnExit _([this]()
    {
        m_signalDispatcherDepth--;
        if ((0 == m_signalDispatcherDepth) && (m_signalsNeedGarbageCollection == true))
        {
            SignalsGarbageCollector();
        }
    });

    auto iter = m_signals.find(signalName);
    if (iter == m_signals.end())
    {
        return;
    }
    auto& signalInfos = (*iter).second;

    oUniStream argsStream;
    const std::vector<uint8_t>* buffPtr = nullptr;
    if (false == signalInfos.empty())
    {
        argsStream.Serialize(args ...);
        const auto& buffRef = argsStream.GetBuffer();
        buffPtr = &buffRef;
        if (buffPtr == nullptr)
        {
            eCDebug(LOG_CATEGORY_BACKTRACE) << "Dispatcher null stream buffer!\n";
            throw "FunctionBinder::DispatchSignal::null buff";
        }
    }

    for (auto& signalInfo : signalInfos)
    {
        auto isAlive = signalInfo.isAliveMarker.lock();
        if (isAlive == nullptr)
        {
            signalInfo.disabled = true;
            m_signalsNeedGarbageCollection = true;
        }

        if (signalInfo.disabled == true)
        {
            continue;
        }
        if (isAlive->IsPaused())
        {
            continue;
        }

        const auto& buff = *buffPtr;
        auto fullArgs = egt::iUniStream(buff);
        signalInfo.functor(fullArgs);
        if (signalInfo.executeOnce == true)
        {
            signalInfo.disabled = true;
            m_signalsNeedGarbageCollection = true;
        }
    }
}

