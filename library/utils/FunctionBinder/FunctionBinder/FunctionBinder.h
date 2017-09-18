#pragma once
#include "../../UniStream/UniStream.h"

#include <functional>
#include <string>
#include <map>
#include <queue>
#include "../BindableObject.h"
#include "../../OnExit.h"
#include "../FunctionCallErrors.h"
#include <thread>

#define SIGNAL_HI_PRIORITY (32)
#define SIGNAL_NORMAL_PRIORITY (64)
#define SIGNAL_LOW_PRIORITY (96)

template <typename T>
struct identity
{
  typedef T type;
};

namespace egt {

class FunctionBinder
{
public:
    typedef std::function<oUniStream(iUniStream&)> FunctionType;
    struct SignalHandlerInfo
    {
    private:
        FunctionType    functor;
        std::weak_ptr<BindableObject> isAliveMarker;
    public:
        u_int64_t       handlerId;
        std::string     signalName;
        uint32_t        priority;
        bool            disabled;
        bool            executeOnce;
        bool operator<(const SignalHandlerInfo& other) const
        {
            return priority < other.priority;
        }
        friend class FunctionBinder;
    };
    typedef std::vector<SignalHandlerInfo> SignalContainer;

    FunctionBinder();
    virtual ~FunctionBinder();

    template<typename InstanceType, typename ... ArgsTypes>
    SignalHandlerInfo ConnectSignal(   const std::string& signalName,
                                InstanceType& instance,
                                void(InstanceType::*func)(ArgsTypes ... args),
                                uint32_t priority = SIGNAL_NORMAL_PRIORITY);

    template<typename InstanceType, typename ... ArgsTypes>
    SignalHandlerInfo ConnectStaticSignal(   const std::string& signalName,
                                InstanceType& instance,
                                std::function<void(ArgsTypes ... args)> func,
                                uint32_t priority = SIGNAL_NORMAL_PRIORITY);

    SignalHandlerInfo ConnectSignal(   const std::string& signalName,
                                        BindableObject& instance,
                                        std::function<void(void)> func,
                                        uint32_t priority = SIGNAL_NORMAL_PRIORITY);

    template<typename InstanceType, typename ResultType, typename ... ArgsTypes>
    bool Register(const std::string& funcName, InstanceType& instance, ResultType (InstanceType::*func)(ArgsTypes ... args));

    template<typename RetType, typename ... ArgsTypes>
    bool RegisterStatic(const std::string& funcName, RetType(*func)(ArgsTypes ... args));

    bool RemoteCallFunction(const std::string& funcName, iUniStream& funcArgs, oUniStream& funcResult);

    bool FunctionExist(const std::string& funcName);

    template<typename ResultType, typename ... ArgsTypes>
    ResultType CallFunction(const std::string& funcName, ArgsTypes ... args);

    template<typename ... ArgsTypes>
    void CallVoidFunction(const std::string& funcName, ArgsTypes ... args);

    template<typename ... ArgsTypes>
    void DispatchSignal(const std::string& signalName, ArgsTypes ... args);

    void DisconnectSignal(u_int64_t signalHandlerId);
    void DisconnectSignal(const SignalHandlerInfo& signalInfo);
    void DisconnectSignal(const std::string& signalName, BindableObject& instance);

protected:

private:

//    FunctionType
//    CreateStaticLambdaFunctor(
//                        std::function<void(void)> func,
//                        bool skipTooManyParametersCheck = false);

    SignalContainer& GetSignalContainer(const std::string& signalName);
    void AddInSignalContainer(SignalContainer& signalContainer, const SignalHandlerInfo& signalInfo);
    u_int64_t GetFreeSignalHandlerId();
    void RemoveSignal(u_int64_t signalHandlerId);
    void RemoveSignal(const SignalHandlerInfo& signalInfo);
    void SignalsGarbageCollector();

#include "FunctionBinderFunctors.hpp"
#include "FunctionBinderStaticFunctors.hpp"

    uint64_t m_lastSignalHandlerId;
    uint32_t m_signalDispatcherDepth;
    bool     m_signalsNeedGarbageCollection;

    std::map<std::string, FunctionType> m_functions;
    std::map<std::string, SignalContainer> m_signals;

    //
    // TEMP
    std::thread::id m_mainThreadId;
};


#include "FunctionBinder.hpp"
oUniStream& operator<< (oUniStream& out, const FunctionBinder::SignalHandlerInfo& handlerInfo);
iUniStream& operator>> (iUniStream& in, FunctionBinder::SignalHandlerInfo& handlerInfo);
}


typedef egt::FunctionBinder::SignalHandlerInfo SignalHandlerInfo;
