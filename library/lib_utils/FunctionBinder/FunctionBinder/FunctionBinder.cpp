#include "FunctionBinder.h"
#include <iostream>
#include <algorithm>

namespace egt
{

///////////////////////////////////////////////////////////////////////////
egt::oUniStream& operator<< (egt::oUniStream& out, const FunctionBinder::SignalHandlerInfo& handlerInfo)
{
    out << handlerInfo.handlerId << handlerInfo.priority << handlerInfo.signalName << handlerInfo.disabled << handlerInfo.executeOnce;
    return out;
}

///////////////////////////////////////////////////////////////////////////
egt::iUniStream& operator>> (egt::iUniStream& in, FunctionBinder::SignalHandlerInfo& handlerInfo)
{
    in >> handlerInfo.handlerId >> handlerInfo.priority >> handlerInfo.signalName >> handlerInfo.disabled >> handlerInfo.executeOnce;
    return in;
}

///////////////////////////////////////////////////////////////////////////
FunctionBinder::FunctionBinder()
    : m_lastSignalHandlerId(0)
    , m_signalDispatcherDepth(0)
    , m_signalsNeedGarbageCollection(false)
    , m_mainThreadId(std::this_thread::get_id())
{

}

///////////////////////////////////////////////////////////////////////////
FunctionBinder::~FunctionBinder()
{

}

///////////////////////////////////////////////////////////////////////////
bool FunctionBinder::RemoteCallFunction(const std::string& funcName, iUniStream& funcArgs,oUniStream& funcResult)
{
    auto p = m_functions.find(funcName);
    if (p == m_functions.end())
    {
        funcResult = oUniStream();
        return false;
    }
    funcResult = p->second(funcArgs);
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool FunctionBinder::FunctionExist(const std::string& funcName)
{
    return (m_functions.find(funcName) != m_functions.end());
}

///////////////////////////////////////////////////////////////////////////
FunctionBinder::SignalContainer& FunctionBinder::GetSignalContainer(const std::string& signalName)
{
    const auto& iter = m_signals.find(signalName);
    if (iter == m_signals.end())
    {
        m_signals[signalName] = SignalContainer();
        return m_signals[signalName];
    }
    else
    {
        return (*iter).second;
    }
}

///////////////////////////////////////////////////////////////////////////
void FunctionBinder::AddInSignalContainer(SignalContainer& signalContainer, const SignalHandlerInfo& signalInfo)
{
    signalContainer.push_back(signalInfo);
    std::sort(signalContainer.begin(), signalContainer.end());
}

///////////////////////////////////////////////////////////////////////////
u_int64_t FunctionBinder::GetFreeSignalHandlerId()
{
    m_lastSignalHandlerId++;
    return m_lastSignalHandlerId;
}

///////////////////////////////////////////////////////////////////////////
void FunctionBinder::DisconnectSignal(u_int64_t signalHandlerId)
{
    for (auto& p : m_signals)
    {
        auto& signalContainer = p.second;
        for (auto signalIter = signalContainer.begin(); signalIter < signalContainer.end(); signalIter++)
        {
            auto& signalInfo = *signalIter;
            if (signalInfo.handlerId == signalHandlerId)
            {
                signalInfo.disabled = true;
                m_signalsNeedGarbageCollection = true;
                break;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void FunctionBinder::DisconnectSignal(const SignalHandlerInfo& signalInfo)
{
    auto iter = m_signals.find(signalInfo.signalName);
    if (iter == m_signals.end())
    {
        return;
    }

    auto& signalContainer = iter->second;
    for (auto signalIter = signalContainer.begin(); signalIter < signalContainer.end(); signalIter++)
    {
        auto& info = *signalIter;
        if (info.handlerId == signalInfo.handlerId)
        {
            info.disabled = true;
            m_signalsNeedGarbageCollection = true;
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void FunctionBinder::DisconnectSignal(const std::string &signalName, BindableObject &instance)
{
    auto iter = m_signals.find(signalName);
    if (iter == m_signals.end())
    {
        return;
    }

    auto marker = instance.GetIsAliveMarker();
    auto locker = marker.lock();

    auto& signalContainer = iter->second;
    for (auto signalIter = signalContainer.begin(); signalIter < signalContainer.end(); signalIter++)
    {
        auto& info = *signalIter;
        auto checkLocker = info.isAliveMarker.lock();
        if (checkLocker == locker)
        {
            info.disabled = true;
            m_signalsNeedGarbageCollection = true;
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void FunctionBinder::RemoveSignal(u_int64_t signalHandlerId)
{
    for (auto& p : m_signals)
    {
        auto& signalContainer = p.second;
        bool jobDone = false;
        for (auto signalIter = signalContainer.begin(); signalIter < signalContainer.end(); signalIter++)
        {
            if (jobDone)
            {
                break;
            }
            const auto& signalInfo = *signalIter;
            if (signalInfo.handlerId == signalHandlerId)
            {
                signalContainer.erase(signalIter);
                jobDone = true;
                break;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void FunctionBinder::RemoveSignal(const SignalHandlerInfo& signalInfo)
{
    auto iter = m_signals.find(signalInfo.signalName);
    if (iter == m_signals.end())
    {
        return;
    }

    auto& signalContainer = iter->second;
    bool jobDone = false;
    for (auto signalIter = signalContainer.begin(); signalIter < signalContainer.end(); signalIter++)
    {
        if (jobDone)
        {
            break;
        }
        const auto& info = *signalIter;
        if (info.handlerId == signalInfo.handlerId)
        {
            signalContainer.erase(signalIter);
            jobDone = true;
            break;
        }
    }
}

///////////////////////////////////////////////////////////////////////////
void FunctionBinder::SignalsGarbageCollector()
{
    m_signalsNeedGarbageCollection = false;
    bool emptyContainers = false;
    for (auto& p : m_signals)
    {
        auto& signalContainer = p.second;
        // remove all disabled signals
        auto new_end = std::remove_if(signalContainer.begin(), signalContainer.end(),
                                      [](const SignalHandlerInfo& handler)
                                      { return handler.disabled; });
        signalContainer.erase(new_end, signalContainer.end());
        if (signalContainer.empty())
        {
            emptyContainers = true;
        }
    }
    if (false == emptyContainers)
    {
        return;
    }
    // clear empty containers
    for (auto iter = m_signals.begin(); iter != m_signals.end(); iter++)
    {
        if ((*iter).second.empty())
        {
            iter = m_signals.erase(iter);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
//FunctionBinder::FunctionType
//FunctionBinder::CreateStaticLambdaFunctor(
//                    std::function<void(void)> func,
//                    bool skipTooManyParametersCheck)
//{
//    auto lambda = [func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
//        func();
//        return (oUniStream());
//    };

//    return FunctionType(lambda);
//}

///////////////////////////////////////////////////////////////////////////
FunctionBinder::SignalHandlerInfo
FunctionBinder::ConnectSignal(  const std::string& signalName,
                                BindableObject& instance,
                                std::function<void()>func,
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
    signalInfo.isAliveMarker = instance.GetIsAliveMarker();

    AddInSignalContainer(signalContainer, signalInfo);
    return signalInfo;
}

}

