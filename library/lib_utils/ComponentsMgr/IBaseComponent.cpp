#include "IBaseComponent.h"
#include <sstream>
#include "pugixml.hpp"
#include "../MGValidate.h"
#include "../BaseComponents/System/ComponentsFactory.h"
#include "../XmlParsers/XmlTools.h"

using namespace egt;

///////////////////////////////////////////////////////////////////////////
const std::string IBaseComponent::s_strXmlNodeName = "name";
const std::string IBaseComponent::s_strXmlNodeType = "type";
const std::string IBaseComponent::s_strXmlNodeClass = "class";
const std::string IBaseComponent::s_strXmlNodeKey = "key";
const std::string IBaseComponent::s_strXmlNodeCompName = "component";
const std::string IBaseComponent::s_strXmlNodeCompContainer = "compcontainer";
const std::string IBaseComponent::s_strXmlNodeCompMgrName = "compmgr";
const std::string IBaseComponent::s_strXmlNodeIncludeName = "include";

CompVector IBaseComponent::m_emptyCompVector;

#define exception int
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
const CompVector& IBaseComponent::GetContainer(const std::string& name) const
{
    const auto& ptr = m_vectorContainer.find(name);
    if (ptr == m_vectorContainer.end())
    {
        return m_emptyCompVector;
    }
    return ptr->second;
}

///////////////////////////////////////////////////////////////////////////
CompVector IBaseComponent::GetContainer(const std::string &name, std::function<bool (IBaseComponentPtr)> predicate) const
{
    const auto& srcContainer = GetContainer(name);
    CompVector result;
    for (auto compPtr : srcContainer)
    {
        if(predicate(compPtr))
        {
            result.push_back(compPtr);
        }
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////
//CompVector& IBaseComponent::GetContainer(const std::string& name)
//{
//    const auto& ptr = m_vectorContainer.find(name);
//    if (ptr == m_vectorContainer.end())
//    {
//        return m_emptyCompVector;
//    }
//    return ptr->second;
//}

///////////////////////////////////////////////////////////////////////////
const CompVectorContainer& IBaseComponent::GetContainers() const
{
    return m_vectorContainer;
}

///////////////////////////////////////////////////////////////////////////
void IBaseComponent::AddToComponentVector(const std::string& vecName, IBaseComponentPtr compPtr)
{
    const auto& ptr = m_vectorContainer.find(vecName);
    if (ptr == m_vectorContainer.end())
    {
        CompVector v;
        v.push_back(compPtr);
        m_vectorContainer[vecName] = v;
    }
    else
    {
        ptr->second.push_back(compPtr);
    }
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ReadType(const pugi::xml_node& xmlNode, std::string& result)
{
    // REMOVE ME
    const auto& attr = xmlNode.attribute(s_strXmlNodeClass.c_str());
    if (false == attr.empty())
    {
        return Read(xmlNode, s_strXmlNodeClass, result);
    }
    ////
    result = xmlNode.name();
    if (result.size() <= 0)
    {
        return false;
    }
    bool startWithSmallLetter = ((result[0] >= 'a') && (result[0] <= 'z'));
    bool startWithCapLetter = ((result[0] >= 'A') && (result[0] <= 'Z'));
    bool startWithLetter = (startWithSmallLetter || startWithCapLetter);

    return (startWithLetter);
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::IsComponent(const pugi::xml_node& xmlNode)
{
    if ((s_strXmlNodeCompMgrName == xmlNode.name()) || (s_strXmlNodeIncludeName == xmlNode.name()))
    {
        // PATCH, CHANGE IT !!!
        // IF IT IS COMP MANAGER OR INCLUDE NODE RETURN FALSE
        return false;
    }
    // CHECK FOR SKIP ATTRIBUTE
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::HasContainer(const std::string& name) const
{
    const auto& ptr = m_vectorContainer.find(name);
    bool result = (ptr != m_vectorContainer.end());

    return result;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::ExtractContainer(std::stringstream& src, std::stringstream& result)
{
    int c;

    while (((c = src.get()) != EOF) && (c != '{'));

    int count = 0;
    while((c = src.get()) != EOF)
    {
        if (c == '{')
        {
            count++;
        }
        else if (c == '}')
        {
            if (0 == count)
            {
                return true;
            }
            count--;
        }
        result << (char)c;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::BaseSerialize(pugi::xml_node& xmlNode) const
{
    const auto& compName = GetComponentName();
    if( false == xmlNode.set_name( compName.c_str() ) )
    {
        COMP_MGR_LOG << "Cant set component xml node name.";
        return false;
    }

    if (false == WriteContainers(xmlNode))
    {
        COMP_MGR_LOG << "Cant save component containers.";
        return false;
    }

    if (false == Serialize(xmlNode))
    {
        COMP_MGR_LOG << "Error component serializing.";
        return false;
    }

    return true;
}

bool IBaseComponent::BaseSerialize(oUniStream& outStream) const
{
    if (!(outStream << (u_int32_t)GetComponentId()))
    {
        COMP_MGR_LOG << "Cant set component ID.";
        return false;
    }
    if (!(outStream << GetComponentHint()))
    {
        COMP_MGR_LOG << "Cant set component hint.";
        return false;
    }
    if (false == WriteContainers(outStream))
    {
        COMP_MGR_LOG << "Cant save component containers.";
        return false;
    }

    if (false == Serialize(outStream))
    {
        COMP_MGR_LOG << "Error component serializing.";
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteContainers(oUniStream& outStream) const
{
    oUniStream allVectors;
    outStream >> oUniInplace(allVectors); // Start in-place

    for (const auto& vecPair : m_vectorContainer)
    {
        //auto vecNode = xmlNode.append_child(vecPair.first.c_str());
        oUniStream vectorStream;
        allVectors >> oUniInplace(vectorStream); // Start in-place
        if (false == WriteVector(vectorStream, vecPair.second, vecPair.first))
        {
            COMP_MGR_LOG << "Error saving vector.";
            return false;
        }
        if (!(allVectors << vectorStream)) // Flush in-place
        {
            return false;
        }
    }

    if (outStream << allVectors) // Flush in-place
    {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteVector(oUniStream& outStream, const CompVector& vec, const std::string& vecName) const
{
    if (!(outStream << vecName))
    {
        COMP_MGR_LOG << "Cant set vec node name.";
        return false;
    }

    for (const auto& compPtr : vec)
    {
        if (false == compPtr->BaseSerialize(outStream))
        {
            COMP_MGR_LOG << "Error component serializing.";
            return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteContainers(pugi::xml_node& xmlNode) const
{
    for (const auto& vecPair : m_vectorContainer)
    {
        auto vecNode = xmlNode.append_child(vecPair.first.c_str());
        if (false == WriteVector(vecNode, vecPair.second, vecPair.first))
        {
            COMP_MGR_LOG << "Error saving vector.";
            return false;
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::WriteVector(pugi::xml_node& xmlNode, const CompVector& vec, const std::string& vecName) const
{
    if (false == xmlNode.set_name(vecName.c_str()))
    {
        COMP_MGR_LOG << "Cant set vec node name.";
        return false;
    }

    for (const auto& compPtr : vec)
    {
        auto compNode = xmlNode.append_child();
        if (false == compPtr->BaseSerialize(compNode))
        {
            COMP_MGR_LOG << "Error component serializing.";
            return false;
        }
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
ComponentMgrPtr IBaseComponent::GetComponentManager() const
{
    if (auto mgrPtr = m_componentManager.lock())
    {
        return mgrPtr;
    }
    return nullptr;
}

///////////////////////////////////////////////////////////////////////////
void IBaseComponent::AutoMergeContainers(IBaseComponentPtr lowPriorityComp, IBaseComponentPtr highPriorityComp, IBaseComponentPtr mergedCompPtr)
{
    for (const auto& compContainerPair : highPriorityComp->GetContainers())
    {
        auto name = compContainerPair.first;
        const auto& compContainer = compContainerPair.second;

        mergedCompPtr->m_vectorContainer[name] = CompVector();
        auto& newContainer = mergedCompPtr->m_vectorContainer[name];

        CopyCompVector(compContainer, newContainer);
    }

    for (const auto& compContainerPair : lowPriorityComp->GetContainers())
    {
        auto name = compContainerPair.first;
        if (mergedCompPtr->HasContainer(name))
        {
            continue;
        }
        const auto& compContainer = compContainerPair.second;

        auto& newContainer = mergedCompPtr->m_vectorContainer[name];

        CopyCompVector(compContainer, newContainer);
    }
}

///////////////////////////////////////////////////////////////////////////
void IBaseComponent::CopyContainers(const IBaseComponent& srcComp, IBaseComponent& dstComp)
{
    const auto& containers = srcComp.GetContainers();
    for (const auto& containerPair : containers)
    {
        std::string containerName = containerPair.first;
        const auto& container = containerPair.second;

        CompVector& newContainer = dstComp.m_vectorContainer[containerName];
        CopyCompVector(container, newContainer);
    }
}

///////////////////////////////////////////////////////////////////////////
bool IBaseComponent::Init()
{
    return true;
}

///////////////////////////////////////////////////////////////////////////
IBaseComponent::ComponentReflections IBaseComponent::Reflections()
{
    return ComponentReflections(*this);
}

///////////////////////////////////////////////////////////////////////////
void IBaseComponent::CopyCompVector(const CompVector& src, CompVector& dst)
{
    dst.clear();
    for (auto compPtr : src)
    {
        auto compCopy = compPtr->CreateCopy();
        dst.push_back(compCopy);
    }
}

///////////////////////////////////////////////////////////////////////////
void IBaseComponent::SetComponentManager(ComponentMgrPtr componentManager)
{
    m_componentManager = componentManager;
    for (auto& compVectorPair : m_vectorContainer)
    {
        for (auto compPtr : compVectorPair.second)
        {
            compPtr->SetComponentManager(componentManager);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
IBaseComponent::ComponentReflections::ComponentReflections(IBaseComponent &baseComp)
    : m_baseComponent(baseComp)
{}

///////////////////////////////////////////////////////////////////////////
std::map<std::string, IBaseComponent::FieldInfo> IBaseComponent::ComponentReflections::GetFieldsInfo() const
{
    return m_baseComponent._getFieldsInfo();
}

///////////////////////////////////////////////////////////////////////////
IBaseComponent::Field IBaseComponent::ComponentReflections::GetField(const std::string &fieldName) const
{
    return m_baseComponent._getField(fieldName);
}

///////////////////////////////////////////////////////////////////////////
void IBaseComponent::ComponentReflections::SetField(const std::string &fieldName, const UniObject &value)
{
    m_baseComponent._setField(fieldName, value);
}

///////////////////////////////////////////////////////////////////////////
void IBaseComponent::ComponentReflections::ClearField(const std::string &fieldName)
{
    m_baseComponent._clearField(fieldName);
}
