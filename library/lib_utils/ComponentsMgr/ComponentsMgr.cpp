#include "ComponentsMgr.h"
#include "IBaseComponent.h"

#include "pugixml.hpp"

#include <iostream>
#include <fstream>
#include <memory>

#include "../BaseComponents/System/ComponentsFactory.h"

#include <lib_utils/MGValidate.h>

using namespace egt;

const std::string ComponentMgr::s_strXmlAttrName = "name";
const std::string ComponentMgr::s_strXmlNodeCompMgr = "compmgr";
const std::string ComponentMgr::s_strXmlNodeInclude = "include";

const std::string ComponentMgr::s_strXmlAttrFileName = "filename";
const std::string ComponentMgr::s_strXmlAttrTagName = "tagname";
const std::string ComponentMgr::s_strXmlAttrSegment = "segment";

#define exception int

///////////////////////////////////////////////////////////////////////////
ComponentMgr::ComponentMgr()
    : m_autoMerge(ComponentsMergeFunc())
    , m_name("")
    , m_components(ComponentsContainer())
    , m_factoryHash(0ul)
{

}

///////////////////////////////////////////////////////////////////////////
ComponentMgr::~ComponentMgr()
{

}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::InitComponents()
{
    bool result = true;
    for(auto& compPair : m_components)
    {
        auto& compPtr = compPair.second;
        if (false == compPtr->Init())
        {
            COMP_MGR_LOG << "Error initing component : " << compPtr->GetComponentName();
            COMP_MGR_LOG << "Component hint : " << compPtr->GetComponentHint();
            result = false;
        }
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::Update()
{
    for (auto& p : m_components)
    {
        auto comp = p.second;
        comp->Update();
    }
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::IsManager(const pugi::xml_node& xmlNode)
{
    std::string name = xmlNode.name();
    return (s_strXmlNodeCompMgr == name);
}

///////////////////////////////////////////////////////////////////////////
ComponentMgrPtr ComponentMgr::Merge(ComponentMgrPtr lowPriorityMgr, ComponentMgrPtr highPriorityMgr, const std::string& managerName, MgrMergeType mergeType)
{
    if (lowPriorityMgr->GetFactoryHash() != highPriorityMgr->GetFactoryHash())
    {
        COMP_MGR_LOG << "Merging managers from different factories : " << lowPriorityMgr->GetName() << ", " << highPriorityMgr->GetName();
        COMP_ASSERT("Merging managers from different factories");

        return nullptr;
    }

    ComponentsContainer c;
    ComponentsContainer& cLow = lowPriorityMgr->m_components;
    ComponentsContainer& cHigh = highPriorityMgr->m_components;

    // Insert all components that exist only in cLow
    for (const auto& p : cLow)
    {
        if( cHigh.find(p.first) == cHigh.end())
        {
            std::pair<IComponentId, IBaseComponentPtr> pairCopy;
            pairCopy.first = p.first;
            pairCopy.second = p.second->CreateCopy();
            c.insert(pairCopy);
        }
    }
    // Insert all components that exist only in c2
    for (const auto& p : cHigh)
    {
        if( cLow.find(p.first) == cLow.end())
        {
            std::pair<IComponentId, IBaseComponentPtr> pairCopy;
            pairCopy.first = p.first;
            pairCopy.second = p.second->CreateCopy();
            c.insert(pairCopy);
        }
    }

    // Merge only conflicted components ( common components for both containers cLow and cHigh)
    for (const auto& p : cLow)
    {
        auto compIterator = cHigh.find(p.first);
        if (compIterator == cHigh.end())
        {
            // we dont have conflict here
            continue;
        }

        const egt::IBaseComponentPtr& lowPriorityComp = p.second;
        const egt::IBaseComponentPtr& highPriorityComp = compIterator->second;
        IComponentId compID = p.first;
        if (compID != compIterator->first)
        {
            COMP_MGR_LOG << "Merging managers fail: " << lowPriorityMgr->GetName() << ", " << highPriorityMgr->GetName();
            COMP_MGR_LOG << "Merging components with different IDs: " << lowPriorityComp->GetComponentName() << ", " << highPriorityComp->GetComponentName();
            COMP_ASSERT("Merging components with different IDs");
        }

        // Resolve different merge modes
        switch (mergeType)
        {
        case MgrMergeType::ASSERT_IF_CONFLICT:
        {
            COMP_MGR_LOG << "Merging managers fail: " << lowPriorityMgr->GetName() << ", " << highPriorityMgr->GetName();
            COMP_MGR_LOG << "Resolving conflict is not allowed  fail : " << lowPriorityComp->GetComponentName() << ", " << highPriorityComp->GetComponentName();
            COMP_ASSERT("Resolving conflict is not allowed  fail");
            return nullptr;
        }
        break;
        case MgrMergeType::AUTO:
        {
            auto newComp = lowPriorityMgr->m_autoMerge(lowPriorityComp, highPriorityComp);
            if (nullptr != newComp)
            {
                c[compID] = newComp;
            }
            else
            {
                COMP_MGR_LOG << "Merging managers fail: " << lowPriorityMgr->GetName() << ", " << highPriorityMgr->GetName();
                COMP_MGR_LOG << "Merging components fail: " << lowPriorityComp->GetComponentName() << ", " << highPriorityComp->GetComponentName();
                COMP_ASSERT("Merging components fail");
            }
        }
        break;
        case MgrMergeType::FORCE_HIGH_PRIORITY_COMP:
        {
            auto newComp = highPriorityComp->CreateCopy();
            c[compID] = newComp;
        }
        break;
        default:
        {
            COMP_MGR_LOG << "Unknown merging type: " << ((int)mergeType) << " - " << lowPriorityMgr->GetName() << ", " << highPriorityMgr->GetName();
            COMP_ASSERT("Unknown merging type");
        }
        break;
        }
    }
    auto ptr = std::make_shared< egt::ComponentMgr >();
    ptr->m_autoMerge = lowPriorityMgr->m_autoMerge;
    ptr->m_factoryHash = lowPriorityMgr->m_factoryHash;

    ptr->m_name = managerName;
    ptr->m_components = c;
    IntroduceManagerToAllComponents(ptr);

    return ptr;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::Serialize(pugi::xml_node& node) const
{
    node.set_name(s_strXmlNodeCompMgr.c_str());
    pugi::xml_attribute mgrNameAttr = node.append_attribute(s_strXmlAttrName.c_str());
    mgrNameAttr.set_value(GetName().c_str());

    for (const auto& comp : m_components)
    {
        pugi::xml_node compNode = node.append_child("");
        if (false == comp.second->BaseSerialize(compNode))
        {
            // ASSERT
            COMP_MGR_LOG << "Error serializing node";
            return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::Serialize(oUniStream& outStream) const
{
    oUniStream mgrStream;
    outStream >> oUniInplace(mgrStream);

    if (!(mgrStream << GetName()))
    {
        // ASSERT
        COMP_MGR_LOG << "Error serializing manager name" << GetName();
        return false;
    }

    oUniStream componentsStream;
    mgrStream >> oUniInplace(componentsStream);

    for (const auto& comp : m_components)
    {
        if (false == comp.second->BaseSerialize(componentsStream))
        {
            // ASSERT
            COMP_MGR_LOG << "Error serializing node";
            return false;
        }
    }
    mgrStream << componentsStream;
    outStream << mgrStream;

    return true;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::Serialize(const std::string& fileName) const
{
    pugi::xml_document document;
    bool loadResult = LoadXML(fileName, document, pugi::parse_default | pugi::parse_pi | pugi::parse_comments);
    if ( !loadResult )
    {
        document.reset();
    }

    if (document.empty())
    {
        document.append_child("Root");
    }
    auto rootNode = document.root();

    auto node = rootNode.append_child(s_strXmlNodeCompMgr.c_str());
    bool serializeResult = Serialize(node);
    document.append_child(pugi::node_comment).set_value(" ==================================== ");
    if (serializeResult)
    {
        serializeResult = document.save_file(fileName.c_str());
    }

    return serializeResult;
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::AddComponent(IBaseComponentPtr compPtr)
{
    if (nullptr == compPtr)
    {
        COMP_MGR_LOG << "Add nullptr component in manager : " << GetName();
        return;
    }
    if( m_components.find(compPtr->GetComponentId()) == m_components.end())
    {
        m_components[compPtr->GetComponentId()] = compPtr;
    }
    else
    {
        COMP_MGR_LOG << "Add duplicate component in manager : " << GetName() << ", " << compPtr->GetComponentName();
    }
}

const std::string &ComponentMgr::GetName() const
{
     return m_name;
}

u_int64_t ComponentMgr::GetFactoryHash() const
{
     return m_factoryHash;
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::IntroduceManagerToAllComponents(ComponentMgrPtr mgr)
{
    for (const auto& compPair : mgr->m_components)
    {
        compPair.second->SetComponentManager(mgr);
    }
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::RegisterManager(const std::string& key, ComponentMgrPtr mgrPtr)
{
    if (nullptr == mgrPtr)
    {
        COMP_MGR_LOG << "Registering NULL manager: " << GetName() << ", " << ", " << key;
        COMP_ASSERT("Registering NULL manager.");
        return;
    }
    if (nullptr != GetRegisteredManager(key))
    {
        COMP_MGR_LOG << "Registering already registered manager: " << GetName() << ", " << mgrPtr->GetName() << ", " << key;
        COMP_ASSERT("Registering already registered manager.");
        return;
    }
    m_managers[key] = mgrPtr; // overwriting old manager if any
}

///////////////////////////////////////////////////////////////////////////
ComponentMgrPtr ComponentMgr::GetRegisteredManager(const std::string& key)
{
    auto mgrIter = m_managers.find(key);
    if (mgrIter == m_managers.end())
    {
        return nullptr;
    }

    if (ComponentMgrPtr mgrSharedPtr = (*mgrIter).second.lock())  // Has to be copied into a shared_ptr before usage
    {
        return mgrSharedPtr;
    }

    UnregisterManager(key);
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////
void ComponentMgr::UnregisterManager(const std::string& key)
{
    m_managers.erase(key);
}

///////////////////////////////////////////////////////////////////////////
IBaseComponentPtr ComponentMgr::GetComponent(IComponentId componentId) const
{
    auto compIterator = m_components.find( componentId );
    if( compIterator == m_components.end())
    {
        return nullptr;
    }
    return compIterator->second;
}

///////////////////////////////////////////////////////////////////////////
IBaseComponentPtr ComponentMgr::GetComponent(const std::string &componentName) const
{
    for (auto compPair : m_components)
    {
        auto compPtr = compPair.second;
        if (compPtr->GetComponentName() == componentName)
        {
            return compPtr;
        }
    }
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::Contain(IComponentId componentId) const
{
    auto compIterator = m_components.find( componentId );
    return (compIterator != m_components.end());
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::ExistInFile (const std::string& fileName, const std::string& mgrName)
{
    pugi::xml_document spxmlDoc;
    bool result = TryLoadXML( fileName, spxmlDoc, pugi::parse_default | pugi::parse_pi);
    if ( !result )
    {
        return false;
    }

    pugi::xml_node mainNode;
    pugi::xpath_node_set xset = spxmlDoc.select_nodes ( "//*" ); // traverse all nodes
    for ( auto it = xset.begin(); it != xset.end(); ++it )
    {
        pugi::xml_node node = it->node();
        std::string nodeName = node.name();

        if (s_strXmlNodeCompMgr != nodeName)
        {
            continue;
        }
        pugi::xml_attribute nameAttribute = node.attribute("name");
        if (nameAttribute.empty())
        {
            continue;
        }
        if (mgrName != nameAttribute.as_string())
        {
            continue;
        }
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
std::vector<std::string> ComponentMgr::FindAllManagersInFile(const std::string& fileName)
{
    pugi::xml_document spxmlDoc;
    bool result = LoadXML(fileName, spxmlDoc, pugi::parse_default | pugi::parse_pi );
    if ( !result )
    {
        return std::vector<std::string>();
    }

    pugi::xml_node mainNode;
    pugi::xpath_node_set xset = spxmlDoc.select_nodes ( "//*" ); // traverse all nodes
    std::vector<std::string> allManagers;
    for ( auto it = xset.begin(); it != xset.end(); ++it )
    {
        pugi::xml_node node = it->node();
        std::string nodeName = node.name();

        if (s_strXmlNodeCompMgr != nodeName)
        {
            continue;
        }

        pugi::xml_attribute nameAttribute = node.attribute("name");
        if (nameAttribute.empty())
        {
            continue;
        }

        std::string mgrName = nameAttribute.as_string();
        allManagers.push_back(mgrName);
    }

    return allManagers;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::LoadXML(const std::string& fileName, pugi::xml_document& documant, unsigned int loaderOptions)
{
#ifdef EGT_DEBUG
    MGValidate::ValidateWithLibXML(fileName);
#endif

    pugi::xml_parse_result result = documant.load_file ( fileName.c_str(), loaderOptions );
    if (result)
    {
        return true;
    }

    COMP_MGR_LOG << "Error in loading xml file : " << fileName;
    COMP_MGR_LOG << "Error description : " << result.description();

    auto offset = result.offset;
    std::string line;
    std::ifstream xmlFile (fileName);
    if (xmlFile.is_open())
    {
        bool hintPrinted = false;
        int lineNumber = 1;
        while ( getline (xmlFile,line) )
        {
            if (offset < static_cast<int>(line.size()))
            {
                COMP_MGR_LOG << "Error in line number : " << lineNumber;
                COMP_MGR_LOG << "'" << line << "'";
                hintPrinted = true;
                break;
            }
            offset -= line.size();
            lineNumber++;
        }
        xmlFile.close();
        if (false == hintPrinted)
        {
            COMP_MGR_LOG << "Unknown line.";
        }
    }
    else
    {
        COMP_MGR_LOG << "Can't open file !";
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool ComponentMgr::TryLoadXML(const std::string& fileName, pugi::xml_document& documant, unsigned int loaderOptions)
{
#ifdef EGT_DEBUG
    MGValidate::ValidateWithLibXML(fileName);
#endif

    pugi::xml_parse_result result = documant.load_file ( fileName.c_str(), loaderOptions );
    if (result)
    {
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
FunctionBinder& ComponentMgr::GetFunctions()
{
    return m_functions;
}

///////////////////////////////////////////////////////////////////////////
const ComponentsContainer& ComponentMgr::GetAllComponents() const
{
    return m_components;
}

void ComponentMgr::SetName(const std::string &name)
{
    m_name = name;
}

ComponentMgrPtr ComponentMgr::CreateMgr()
{
    return std::make_shared< ComponentMgr >();
}

ComponentMgrPtr ComponentMgr::CreateMgr(const std::string &mgrName)
{
     ComponentMgrPtr ptr = std::make_shared< ComponentMgr >();
     ptr->m_name = mgrName;
     return ptr;
}
