///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/// FUNCTIONS WITH RETURN TYPE
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(void),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)();
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}


///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType,
         typename ArgType01>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(ArgType01),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};       
        stream >> t1;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)(t1);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType,
         typename ArgType01, typename ArgType02>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(ArgType01, ArgType02),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};       
        typename std::decay<ArgType02>::type t2{};
        stream >> t1 >> t2;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)(t1, t2);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(ArgType01, ArgType02, ArgType03),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};       
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        
        stream >> t1 >> t2 >> t3;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)(t1, t2, t3);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};       
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        
        stream >> t1 >> t2 >> t3 >> t4;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)(t1, t2, t3, t4);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                                    ArgType05),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};       
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        typename std::decay<ArgType05>::type t5{};
        stream >> t1 >> t2 >> t3 >> t4 >> t5;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)(t1, t2, t3, t4, t5);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                                     ArgType05, ArgType06),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};       
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        typename std::decay<ArgType05>::type t5{};
        typename std::decay<ArgType06>::type t6{};
        
        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)(t1, t2, t3, t4, t5, t6);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06, typename ArgType07>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                                     ArgType05, ArgType06, ArgType07),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};       
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        typename std::decay<ArgType05>::type t5{};
        typename std::decay<ArgType06>::type t6{};
        typename std::decay<ArgType07>::type t7{};
        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)(t1, t2, t3, t4, t5, t6, t7);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType, typename ResultType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06, typename ArgType07, typename ArgType08>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    ResultType (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                                     ArgType05, ArgType06, ArgType07, ArgType08),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};       
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        typename std::decay<ArgType05>::type t5{};
        typename std::decay<ArgType06>::type t6{};
        typename std::decay<ArgType07>::type t7{};
        typename std::decay<ArgType08>::type t8{};

        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7 >> t8;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        ResultType res = (instance->*func)(t1, t2, t3, t4, t5, t6, t7, t8);
        oUniStream oStream;
        oStream << res;

        return (oStream);
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
/// VOID FUNCTIONS
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
template<typename InstanceType>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(void),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)();

        return (oUniStream());
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType,
         typename ArgType01>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(ArgType01),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};
        stream >> t1;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)(t1);

        return (oUniStream());
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType,
         typename ArgType01, typename ArgType02>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(ArgType01, ArgType02),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};
        typename std::decay<ArgType02>::type t2{};

        stream >> t1 >> t2;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)(t1, t2);

        return (oUniStream());
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType,
         typename ArgType01, typename ArgType02, typename ArgType03>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(ArgType01, ArgType02, ArgType03),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        stream >> t1 >> t2 >> t3;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)(t1, t2, t3);

        return (oUniStream());
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        
        stream >> t1 >> t2 >> t3 >> t4;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)(t1, t2, t3, t4);

        return (oUniStream());
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                               ArgType05),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        typename std::decay<ArgType05>::type t5{};

        stream >> t1 >> t2 >> t3 >> t4 >> t5;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)(t1, t2, t3, t4, t5);

        return (oUniStream());
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                               ArgType05, ArgType06),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        typename std::decay<ArgType05>::type t5{};
        typename std::decay<ArgType06>::type t6{};

        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)(t1, t2, t3, t4, t5, t6);

        return (oUniStream());
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06, typename ArgType07>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                               ArgType05, ArgType06, ArgType07),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        typename std::decay<ArgType05>::type t5{};
        typename std::decay<ArgType06>::type t6{};
        typename std::decay<ArgType07>::type t7{};

        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)(t1, t2, t3, t4, t5, t6, t7);

        return (oUniStream());
    };

    return FunctionType(lambda);
}

///////////////////////////////////////////////////////////////////////////
template<typename InstanceType,
         typename ArgType01, typename ArgType02, typename ArgType03, typename ArgType04,
         typename ArgType05, typename ArgType06, typename ArgType07, typename ArgType08>
FunctionType
CreateFunctor(
                    InstanceType* instance,
                    void (InstanceType::*func)(ArgType01, ArgType02, ArgType03, ArgType04,
                                               ArgType05, ArgType06, ArgType07, ArgType08),
                    bool skipTooManyParametersCheck = false)
{
    auto lambda = [instance, func, skipTooManyParametersCheck](iUniStream& stream)->oUniStream {
        typename std::decay<ArgType01>::type t1{};
        typename std::decay<ArgType02>::type t2{};
        typename std::decay<ArgType03>::type t3{};
        typename std::decay<ArgType04>::type t4{};
        typename std::decay<ArgType05>::type t5{};
        typename std::decay<ArgType06>::type t6{};
        typename std::decay<ArgType07>::type t7{};
        typename std::decay<ArgType08>::type t8{};

        stream >> t1 >> t2 >> t3 >> t4 >> t5 >> t6 >> t7 >> t8;
        if (!stream)
        {
            throw "Not enought parameters";
        }
        if ((false == skipTooManyParametersCheck) && (false == stream.IsEmpty()))
        {
            throw "Too many parameters";
        }
        (instance->*func)(t1, t2, t3, t4, t5, t6, t7, t8);

        return (oUniStream());
    };

    return FunctionType(lambda);
}
