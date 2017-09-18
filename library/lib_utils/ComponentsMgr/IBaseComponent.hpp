#ifndef IBASECOMPONENT_HPP
#define IBASECOMPONENT_HPP


///////////////////////////////////////////////////////////////////////////
template<typename T>
std::vector< std::shared_ptr<T> > IBaseComponent::GetContainer(const std::string& name, std::function<bool(std::shared_ptr<T>)> predicate) const
{
    std::vector<std::shared_ptr<T>> result;
    const auto& baseVect = GetContainer(name);
    for(const auto& comp : baseVect)
    {
         std::shared_ptr<T> ptr = T::SafeCast(comp);
         if (nullptr != ptr)
         {
             if (nullptr == predicate || true == predicate(ptr))
             {
                result.push_back(ptr);
             }
         }
    }

    // It is required this cast about bug into cppcheck tool
    return static_cast<std::vector<std::shared_ptr<T>>> ( result );
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool IBaseComponent::ReadVector(const pugi::xml_node& containerNode)
{
    std::string contName;

    // REMOVE ME
    if (s_strXmlNodeCompContainer == containerNode.name())
    {
        if ((false == Read(containerNode, s_strXmlNodeName, contName)) || (contName.empty()))
        {
            return false;
        }
    }
    else
    {
        contName = containerNode.name();
    }

    if (m_vectorContainer.find(contName) != m_vectorContainer.end())
    {
        COMP_MGR_LOG << "Duplicate container error : " << contName << ", " << GetComponentName();
        return false;
    }

    m_vectorContainer[contName] = CompVector();
    auto& vec = m_vectorContainer[contName];

    for (const auto& compNode : containerNode.children())
    {
        auto c = ComponentFactoryType::CreateComponent(compNode);
        if (nullptr == c)
        {
            COMP_MGR_LOG << "Error parsing container components: " << contName << ", " << compNode.name();
            return false;
        }
        vec.push_back(c);
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool IBaseComponent::ReadVector(iUniStream& containerStream)
{
    std::string contName;
    if (!(containerStream >> contName))
    {
        COMP_MGR_LOG << "Error reading vector name " << GetComponentName();
        return false;
    }
    if (m_vectorContainer.find(contName) != m_vectorContainer.end())
    {
        COMP_MGR_LOG << "Duplicate container error(2) : " << contName << ", " << GetComponentName();
        return false;
    }

    m_vectorContainer[contName] = CompVector();
    auto& vec = m_vectorContainer[contName];
    while(!containerStream.IsEmpty())
    {
        auto c = ComponentFactoryType::CreateComponent(containerStream);
        if (nullptr == c)
        {
            COMP_MGR_LOG << "Error parsing container components(2): " << contName << ", " << GetComponentName();
            return false;
        }
        vec.push_back(c);
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool IBaseComponent::BaseLoad(const pugi::xml_node& xmlNode)
{
    ReadContainers<ComponentFactoryType>(xmlNode);

    auto result = Load(xmlNode);

    return result;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool IBaseComponent::BaseLoad(iUniStream& inputStream)
{
    // The component ID is already read by component factory
    // ...

    std::string compHint;
    if (!(inputStream >> compHint))
    {
        COMP_MGR_LOG << "Cant read component hint from iStream : " << GetComponentName();
        return false;
    }
    SetComponentHint(compHint);

    ReadContainers<ComponentFactoryType>(inputStream);

    auto result = Load(inputStream);

    return result;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool IBaseComponent::ReadContainers(const pugi::xml_node& xmlNode)
{
    try
    {
        for (const auto& containerNode : xmlNode.children())
        {
            if (false == ReadVector<ComponentFactoryType>(containerNode))
            {
                return false;
            }
        }
    }
    catch(int& e)
    {
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool IBaseComponent::ReadContainers(iUniStream& inputStream)
{
    iUniStream allVectors;

    if (!(inputStream >> iUniInplace(allVectors)))
    {
        COMP_MGR_LOG << "Error extracting all vectors stream : " << GetComponentName();
        return false;
    }

    while (!allVectors.IsEmpty())
    {
        iUniStream vectorStream;
        if (!(inputStream >> iUniInplace(vectorStream)))
        {
            COMP_MGR_LOG << "Error extracting vector stream : " << GetComponentName();
            return false;
        }
        if (false == ReadVector<ComponentFactoryType>(vectorStream))
        {
            COMP_MGR_LOG << "Error extracting vector : " << GetComponentName();
            return false;
        }
    }

    return true;
}

template<typename T>
bool IBaseComponent::Write(pugi::xml_node xmlNode, const std::string& fieldName, const T& value)
{
    auto attr = xmlNode.append_attribute(fieldName.c_str());
    std::stringstream s;
    if (false == WriteToStream(s, value))
    {
        COMP_MGR_LOG << "Error saving value";
        return false;
    }

    std::string strVal = s.str();
    if (false == attr.set_value(strVal.c_str()))
    {
        COMP_MGR_LOG << "Cant set attribute value.";
        return false;
    }

    return true;
}

template<typename ValueType>
bool IBaseComponent::ComponentReflections::GetFieldValue(const std::string fieldName, ValueType& value)
{
    auto fieldsInfo = GetFieldsInfo();
    if (fieldsInfo.find(fieldName) == fieldsInfo.end())
    {
        return false;
    }
    auto fieldObj = GetField(fieldName);
    fieldObj.value >> value;

    return true;
}

#include "IBaseComponentBasicReaders.hpp"
#include "IBaseComponentBasicWriters.hpp"
#include "IBaseComponentHashes.hpp"
#include "IBaseComponentTypes.hpp"

#endif // IBASECOMPONENT_HPP
