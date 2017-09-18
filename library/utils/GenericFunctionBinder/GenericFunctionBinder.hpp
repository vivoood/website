#ifndef _GENERIC_FUNCTION_BINDER_HPP_
#define _GENERIC_FUNCTION_BINDER_HPP_

#include <algorithm>
#include <cassert>
#include <functional>
#include <memory>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include <../nonstd/any.hpp>
#include <../nonstd/function_traits.hpp>
#include <../nonstd/optional.hpp>
#include <../nonstd/type_traits.hpp>

#include <TaskMgr.h>

namespace egt
{

class Bindable : public std::enable_shared_from_this<Bindable>
{
public:
    using WeakPtr = std::weak_ptr<Bindable>;
    using Ptr = std::shared_ptr<Bindable>;

    virtual ~Bindable() = default;
    virtual bool IsPaused() const;
    virtual void SetPaused(bool paused);
    WeakPtr GetWeakPtr();

protected:
    std::atomic_bool m_isPaused = {false};
};

namespace detail
{

// Used for type deduction ease
struct void_func
{
    using type = void_func;
};

// Used for type deduction ease
struct return_func
{
    using type = return_func;
};

// Function wrapper used for storage and invoke
template <typename Serializer, typename Deserializer>
struct function_wrapper
{

    struct CallbackInfoStruct
    {
        egt::TaskMgr::Id taskId = 0;
        /// Subscription id
        std::uint64_t id = 0;
        /// Priority used for sorting
        std::uint32_t priority = 0;
        /// Sentinel used for life tracking
        nonstd::optional<Bindable::WeakPtr> sentinel;
        /// The function wrapper
        std::shared_ptr<detail::function_wrapper<Serializer, Deserializer>> function;
    };

    virtual ~function_wrapper() = default;

    virtual Deserializer invoke(Deserializer& params) const = 0;
    virtual void invoke_multithreaded(Deserializer& params, const CallbackInfoStruct& callbackInfo) const = 0;
};

template <typename Serializer, typename Deserializer, typename F>
class function_wrapper_t : public function_wrapper<Serializer, Deserializer>
{
    using CallbackInfo = typename function_wrapper<Serializer, Deserializer>::CallbackInfoStruct;
    Deserializer invoke_variadic_impl(Deserializer& params) const
    {
        static const auto deduction_helper =
            typename std::conditional<std::is_same<typename nonstd::fn_result_of<F>, void>::value, void_func,
                                      return_func>::type();
        return invoke(deduction_helper, params);
    }

    Deserializer invoke(const void_func&, Deserializer& params) const
    {
        typename nonstd::function_traits<F>::arg_types_decayed tuple;
        nonstd::for_each_in_tuple(tuple, [&params](auto& item) { params >> item; });
        nonstd::apply(m_function, tuple);
        return Deserializer();
    }

    Deserializer invoke(const return_func&, Deserializer& params) const
    {
        typename nonstd::function_traits<F>::arg_types_decayed tuple;
        nonstd::for_each_in_tuple(tuple, [&params](auto& item) { params >> item; });
        auto return_value = nonstd::apply(m_function, tuple);

        Serializer serializer;
        serializer << return_value;
        return Deserializer(std::move(serializer));
    }

public:
    using delegate_t = std::function<typename nonstd::function_traits<F>::function_type>;
    ~function_wrapper_t() = default;

    template <typename C>
    function_wrapper_t(C* const object_ptr, F&& f)
        : m_function(nonstd::bind_mem_variadic(object_ptr, std::forward<F>(f)))
    {
    }

    function_wrapper_t(F&& f)
        : m_function(f)
    {
    }

    virtual Deserializer invoke(Deserializer& params) const
    {
        return invoke_variadic_impl(params);
    }

    virtual void invoke_multithreaded(Deserializer& params, const CallbackInfo& callbackInfo) const
    {

        typename nonstd::function_traits<F>::arg_types_decayed tuple;
        nonstd::for_each_in_tuple(tuple, [&params](auto& item) {
            if(!(params >> item))
            {
                throw "cannot deserialize argument";
            }

        });

        if(callbackInfo.sentinel.has_value() == true)
        {
            TaskMgr::Invoke(
                callbackInfo.taskId, callbackInfo.sentinel.value(),
                [ function = m_function, args = std::move(tuple) ]() { nonstd::apply(function, args); });
        }
        else
        {
            TaskMgr::Invoke(callbackInfo.taskId, [ function = m_function, args = std::move(tuple) ]() {
                nonstd::apply(function, args);
            });
        }
    }

private:
    delegate_t m_function;
};

template <typename Serializer, typename Deserializer, typename F>
std::shared_ptr<function_wrapper<Serializer, Deserializer>> make_wrapper(F&& f)
{
    using wrapper = function_wrapper_t<Serializer, Deserializer, F>;
    return std::make_shared<wrapper>(std::forward<F>(f));
}

template <typename Serializer, typename Deserializer, typename C, typename F>
std::shared_ptr<function_wrapper<Serializer, Deserializer>> make_wrapper(C* const object_ptr, F&& f)
{
    using wrapper = function_wrapper_t<Serializer, Deserializer, F>;
    return std::make_shared<wrapper>(object_ptr, std::forward<F>(f));
}

} // namespace detail

template <typename Serializer, typename Deserializer>
class GenericFunctionBinder
{
    std::atomic<std::uint64_t> m_freeId = {1};
    std::uint64_t GetNextId()
    {
        return m_freeId++;
    }

    using CallbackInfo =
        typename ::egt::detail::function_wrapper<Serializer, Deserializer>::CallbackInfoStruct;
    using Bindable = ::egt::Bindable;

public:
    template <typename F>
    std::uint64_t ConnectSlot(const std::string& signalName, Bindable::WeakPtr sentinel, F&& slot,
                              std::uint32_t priority = 0)
    {
        static_assert(std::is_same<void, typename nonstd::function_traits<F>::result_type>::value,
                      "signals cannot have a return type different from void");

        auto id = GetNextId();
        CallbackInfo info;
        info.taskId = TaskMgr::GetId();
        info.id = id;
        info.priority = priority;
        info.sentinel = sentinel;
        info.function = detail::make_wrapper<Serializer, Deserializer>(std::forward<F>(slot));

        TaskMgr::RunOrInvoke(m_threadId, m_lifetimeGuard, [ this, signalName, info = std::move(info) ]() {
            auto& container = m_signals[signalName];
            container.emplace_back(std::move(info));
            Sort(container);
        });

        return id;
    }

    template <typename C, typename F>
    std::uint64_t ConnectSlot(const std::string& signalName, Bindable::WeakPtr sentinel, C* const object,
                              F&& slot, std::uint32_t priority = 0)
    {
        static_assert(std::is_same<void, typename nonstd::function_traits<F>::result_type>::value,
                      "signals cannot have a return type different from void");

        auto id = GetNextId();
        CallbackInfo info;
        info.taskId = TaskMgr::GetId();
        info.id = id;
        info.priority = priority;
        info.sentinel = sentinel;
        info.function = detail::make_wrapper<Serializer, Deserializer>(object, std::forward<F>(slot));

        TaskMgr::RunOrInvoke(m_threadId, m_lifetimeGuard, [ this, signalName, info = std::move(info) ]() {
            auto& container = m_signals[signalName];
            container.emplace_back(std::move(info));
            Sort(container);
        });

        return id;
    }

    template <typename F>
    std::uint64_t ConnectSlot(const std::string& signalName, F&& slot, std::uint32_t priority = 0)
    {
        static_assert(std::is_same<void, typename nonstd::function_traits<F>::result_type>::value,
                      "signals cannot have a return type different from void");

        auto id = GetNextId();
        CallbackInfo info;
        info.taskId = TaskMgr::GetId();
        info.id = id;
        info.priority = priority;
        info.function = detail::make_wrapper<Serializer, Deserializer>(std::forward<F>(slot));

        TaskMgr::RunOrInvoke(m_threadId, m_lifetimeGuard, [ this, signalName, info = std::move(info) ]() {
            auto& container = m_signals[signalName];
            container.emplace_back(std::move(info));
            Sort(container);
        });

        return id;
    }

    template <typename C, typename F>
    std::uint64_t ConnectSlot(const std::string& signalName, C* const object, F&& slot,
                              std::uint32_t priority = 0)
    {
        static_assert(std::is_same<void, typename nonstd::function_traits<F>::result_type>::value,
                      "signals cannot have a return type different from void");

        auto id = GetNextId();
        CallbackInfo info;
        info.taskId = TaskMgr::GetId();
        info.id = id;
        info.priority = priority;
        info.function = detail::make_wrapper<Serializer, Deserializer>(object, std::forward<F>(slot));

        TaskMgr::RunOrInvoke(m_threadId, m_lifetimeGuard, [ this, signalName, info = std::move(info) ]() {
            auto& container = m_signals[signalName];
            container.emplace_back(std::move(info));
            Sort(container);
        });

        return id;
    }

    void DisconnectSlot(const std::string& signalName, std::uint64_t slotId)
    {
        TaskMgr::RunOrInvoke(m_threadId, m_lifetimeGuard, [this, signalName, slotId]() {
            auto& container = m_signals[signalName];

            auto it = std::find_if(std::begin(container), std::end(container),
                                   [&slotId](const CallbackInfo& info) { return info.id == slotId; });

            if(it != std::end(container))
            {
                auto& info = *it;
                info.sentinel = Bindable::WeakPtr();
            }
        });
    }

    template <typename... Args>
    void DispatchSignal(const std::string& signalName, Args&&... args) const
    {
        Serializer serialziedArgs;
        serialziedArgs.Serialize(std::forward<Args>(args)...);
        auto& buffer = serialziedArgs.GetStorage();

        TaskMgr::RunOrInvoke(m_threadId, m_lifetimeGuard,
                             [ this, signalName, bufferRvalue = std::move(buffer) ]() mutable {
                                 const auto taskId = TaskMgr::GetId();
                                 bool collectGarbage = false;

                                 const auto& buffer = bufferRvalue;

                                 auto& container = m_signals[signalName];
                                 // Iterate this way to allow addition
                                 for(size_t i = 0; i < container.size(); ++i)
                                 {
                                     const auto& info = container[i];
                                     Bindable::Ptr sentinel = nullptr;
                                     if(info.sentinel.has_value())
                                     {
                                         sentinel = info.sentinel.value().lock();
                                         if(nullptr == sentinel)
                                         {
                                             collectGarbage = true;
                                         }
                                         if(nullptr == sentinel || sentinel->IsPaused())
                                         {
                                             continue;
                                         }
                                     }
                                     Deserializer params(buffer);

                                     if(info.taskId == taskId)
                                     {
                                         info.function->invoke(params);
                                     }
                                     else
                                     {
                                         info.function->invoke_multithreaded(params, info);
                                     }
                                 }

                                 if(collectGarbage)
                                 {
                                     ClearGarbage(container);
                                     // If it was the last one, remove the whole container
                                     if(container.empty())
                                         m_signals.erase(signalName);
                                 }
                             });
    }

    template <typename F>
    std::uint64_t BindFunction(const std::string& functionName, Bindable::WeakPtr sentinel, F&& function)
    {
        assert(m_threadId == std::this_thread::get_id() && "Using binder from a different thread");

        auto id = GetNextId();
        CallbackInfo info;
        info.id = id;
        info.sentinel = sentinel;
        info.function = detail::make_wrapper<Serializer, Deserializer>(std::forward<F>(function));
        m_functions.emplace(functionName, std::move(info));
        return id;
    }

    template <typename C, typename F>
    std::uint64_t BindFunction(const std::string& functionName, Bindable::WeakPtr sentinel, C* const object,
                               F&& function)
    {
        assert(m_threadId == std::this_thread::get_id() && "Using binder from a different thread");

        auto id = GetNextId();
        CallbackInfo info;
        info.id = id;
        info.sentinel = sentinel;
        info.function = detail::make_wrapper<Serializer, Deserializer>(object, std::forward<F>(function));
        m_functions.emplace(functionName, std::move(info));

        return id;
    }

    template <typename R, typename... Args,
              typename std::enable_if<!std::is_same<R, void>::value>::type* = nullptr>
    R CallFunction(const std::string& id, Args&&... args) const
    {
        assert(m_threadId == std::this_thread::get_id() && "Using binder from a different thread");

        static_assert(!std::is_reference<R>::value, "unsupported return by reference (use return by value)");
        R res{};

        auto it = m_functions.find(id);
        if(it == m_functions.end())
            return res;

        const auto& info = it->second;

        // check if subscriber expired
        Bindable::Ptr sentinel = nullptr;
        if(info.sentinel.has_value())
        {
            sentinel = info.sentinel.value().lock();
            if(nullptr == sentinel)
            {
                m_functions.erase(it);
            }
            if(nullptr == sentinel)
            {
                return res;
            }
        }

        if(info.function != nullptr)
        {
            Serializer serialziedArgs;
            serialziedArgs.Serialize(std::forward<Args>(args)...);
            Deserializer params(std::move(serialziedArgs));

            Deserializer result = info.function->invoke(params);
            result >> res;
        }
        return res;
    }

    template <typename R = void, typename... Args,
              typename std::enable_if<std::is_same<R, void>::value>::type* = nullptr>
    R CallFunction(const std::string& id, Args&&... args) const
    {
        assert(m_threadId == std::this_thread::get_id() && "Using binder from a different thread");

        static_assert(!std::is_reference<R>::value, "unsupported return by reference (use return by value)");

        auto it = m_functions.find(id);
        if(it == m_functions.end())
            return;

        const auto& info = it->second;

        // check if subscriber expired
        Bindable::Ptr sentinel = nullptr;
        if(info.sentinel.has_value())
        {
            sentinel = info.sentinel.value().lock();
            if(nullptr == sentinel)
            {
                m_functions.erase(it);
            }
            if(nullptr == sentinel)
            {
                return;
            }
        }

        if(info.function != nullptr)
        {
            Serializer serialziedArgs;
            serialziedArgs.Serialize(std::forward<Args>(args)...);
            Deserializer params(std::move(serialziedArgs));

            info.function->invoke(params);
        }
    }

private:
    static void Sort(std::vector<CallbackInfo>& container)
    {
        std::sort(std::begin(container), std::end(container),
                  [](const auto& info1, const auto& info2) { return info1.priority > info2.priority; });
    }

    static void ClearGarbage(std::vector<CallbackInfo>& container)
    {
        // remove expired subscribers
        container.erase(std::remove_if(std::begin(container), std::end(container),
                                       [](const auto& info) {
                                           return info.sentinel.has_value() &&
                                                  info.sentinel.value().expired();
                                       }),
                        std::end(container));
    }

    static std::shared_ptr<void> init_lifeguard()
    {
        TaskMgr::RegisterThisThread();
        auto var = std::make_shared<bool>();
        return var;
    }

    /// signal / slots
    mutable std::unordered_map<std::string, std::vector<CallbackInfo>> m_signals;
    /// binded fucntions
    mutable std::unordered_map<std::string, CallbackInfo> m_functions;

    std::thread::id m_threadId = std::this_thread::get_id();

    std::shared_ptr<void> m_lifetimeGuard = init_lifeguard();
};
}
#endif
