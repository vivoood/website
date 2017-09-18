/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef _COMPONENTS_MGR_H_
#define _COMPONENTS_MGR_H_

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <sstream>

#include "ComponentsMgrFwd.h"

#include "IBaseComponent.h"
#include "../FunctionBinder/FunctionBinder/FunctionBinder.h"
#include "ComponentLogger.h"

#include <algorithm>
#include <cctype>

namespace pugi
{
    class xml_node;
    class xml_document;
}

/**
 egt namespace.
 */

namespace egt {

class ComponentMgr
{
public:
    using Getter = std::function<egt::ComponentMgrPtr(int id)>;

    ComponentMgr();
    ~ComponentMgr();
    bool InitComponents();
    void Update();

    template<class ComponentFactoryType>
    static ComponentMgrPtr CreateEmptyMgr(const std::string& mgrName);

    template<class ComponentFactoryType>
    static ComponentMgrPtr CreateFromFile (const std::string& fileName, const std::string& mgrName = "");

    template<class ComponentFactoryType>
    static ComponentMgrPtr CreateFromStream (iUniStream& inpStream);

    template<class ComponentFactoryType>
    bool LoadFromFile (const std::string& fileName);

    static bool ExistInFile (const std::string& fileName, const std::string& mgrName);
    static std::vector<std::string> FindAllManagersInFile(const std::string& fileName);

    bool Serialize(const std::string& fileName) const;
    bool Serialize(pugi::xml_node& node) const;
    bool Serialize(oUniStream& outStream) const;

    template <typename T>
    std::shared_ptr<T> GetComponent() const;
    IBaseComponentPtr GetComponent(IComponentId componentId) const;
    IBaseComponentPtr GetComponent(const std::string& componentName) const;

    bool Contain(IComponentId componentId) const;

    template<class ComponentFactoryType>
    bool LoadFromXmlNode(const pugi::xml_node& xmlNode, std::string hint = std::string() );

    template<class ComponentFactoryType>
    bool AddXmlNode(const pugi::xml_node& xmlNode, const std::string& hint);

    template<class ComponentFactoryType>
    bool AddComponent(const pugi::xml_node& xmlNode, const std::string& hint);
    void AddComponent(IBaseComponentPtr compPtr);

    template<class ComponentFactoryType>
    bool AddIncludeFile(const pugi::xml_node& xmlNode);

    const std::string& GetName() const;
    u_int64_t GetFactoryHash() const;

    static bool IsManager(const pugi::xml_node& xmlNode);

    static ComponentMgrPtr Merge(ComponentMgrPtr lowPriorityMgr, ComponentMgrPtr highPriorityMgr, const std::string& managerName = "", MgrMergeType mergeType = MgrMergeType::AUTO);

    static void IntroduceManagerToAllComponents(ComponentMgrPtr mgr);
    void RegisterManager(const std::string& key, ComponentMgrPtr mgrPtr);
    void UnregisterManager(const std::string& key);
    ComponentMgrPtr GetRegisteredManager(const std::string& key);
    FunctionBinder& GetFunctions();
    const ComponentsContainer& GetAllComponents() const;

    using CreateEmptyMgrFunction = void (*)(egt::ComponentMgrPtr& result, const std::string& mgrName);
    using CreateFromFileFunction = void (*)(egt::ComponentMgrPtr& result, const std::string& fileName, const std::string& mgrName);
    using CreateFromStreamFunction = void(*)(egt::ComponentMgrPtr& result, egt::iUniStream& inpStream);
    using GetFactoryHashFunction = void(*)(uint64_t& result);
    using AutoMergeFunction = void(*)(egt::IBaseComponentPtr& result, const egt::IBaseComponentPtr& lowPriorityCompPtr, const egt::IBaseComponentPtr& highPriorityCompPtr);
    using GetComponentsFunction = void(*)(std::map<int, std::string>& result);
    using AddToExistingMgrInFileFunction = bool(*)(const std::string& fileName, ComponentMgrPtr newMgr);
    using ReplaceExistingMgrInFileFunction = bool (*)(const std::string& fileName, ComponentMgrPtr newMgr);
    using BeautifyComponentsXmlFunction = bool(*)(const std::string& fileName);
    using CreateComponentFunction = IBaseComponentPtr (*)(const std::string& compName);
    using MergeManagersFunction = ComponentMgrPtr (*)(ComponentMgrPtr lowPriorityMgr, ComponentMgrPtr highPriorityMgr);


protected:
    void SetName(const std::string& name);
private:
    static ComponentMgrPtr CreateMgr();
    static ComponentMgrPtr CreateMgr(const std::string& mgrName);
    static bool LoadXML(const std::string& fileName, pugi::xml_document& documant, unsigned int loaderOptions);
    static bool TryLoadXML(const std::string& fileName, pugi::xml_document& documant, unsigned int loaderOptions);
    template<class ComponentFactoryType>
    bool InitMgr();

    static const std::string s_strXmlAttrName;
    static const std::string s_strXmlNodeCompMgr;
    static const std::string s_strXmlNodeInclude;

    static const std::string s_strXmlAttrFileName;
    static const std::string s_strXmlAttrTagName;
    static const std::string s_strXmlAttrSegment;

    ComponentsMergeFunc                         m_autoMerge;
    std::string                                 m_name;
    ComponentsContainer                         m_components;
    u_int64_t                                   m_factoryHash;
    std::map<std::string, ComponentMgrWeakPtr>  m_managers;
    FunctionBinder                              m_functions;

};

#include "ComponentsMgr.hpp"

} // namespace egt

#endif // _COMPONENTS_MGR_H_
