#ifndef COMPONENTSMGRINTERFACE_H
#define COMPONENTSMGRINTERFACE_H

#include <functional>
#include <map>
#include <vector>
#include <memory>


namespace egt {

class AnyStream;
class iUniStream;
class oUniStream;
template<typename Serializer, typename Deserializer>
struct GenericMsg;

class IBaseComponent;
class ComponentMgr;

typedef unsigned int IComponentId;
class FunctionBinder;
typedef std::shared_ptr<IBaseComponent> IBaseComponentPtr;
typedef std::weak_ptr<IBaseComponent> IBaseComponentWeakPtr;
typedef std::shared_ptr<ComponentMgr> ComponentMgrPtr;
typedef std::weak_ptr<ComponentMgr> ComponentMgrWeakPtr;
typedef std::map<IComponentId, IBaseComponentPtr> ComponentsContainer;
typedef std::vector<IBaseComponentPtr> CompVector;
typedef std::map<std::string, CompVector> CompVectorContainer;
typedef std::function<ComponentMgrPtr()> ComponentMgrGetter;

namespace  ComponentMsgTypes
{

using LocalMsg = GenericMsg<AnyStream, AnyStream>;
using RemoteMsg = GenericMsg<oUniStream, iUniStream>;

}

#define COMP_LOG  (egt::ComponentLogger().Get())

#define COMP_MGR_LOG (egt::ComponentLogger().Get())

#define COMP_ASSERT(msg) throw msg

enum class MgrMergeType
{
    AUTO,
    FORCE_HIGH_PRIORITY_COMP,
    ASSERT_IF_CONFLICT,
};

typedef egt::IBaseComponentPtr (*ComponentsMergeFunc)(const egt::IBaseComponentPtr& lowPriorityComp, const egt::IBaseComponentPtr& highPriorityComp);

}


#endif // COMPONENTSMGRINTERFACE_H
