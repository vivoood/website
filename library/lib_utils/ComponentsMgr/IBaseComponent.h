/*
 * Author: Nikolay Nedelchev
 *
 * Copyright (c) 2016 EGT Ltd.
 * All rights reserved
 *
 * More information at: http://www.egt-bg.com
 */

#ifndef I_BASE_COMPONENT_H_
#define I_BASE_COMPONENT_H_
#include "ComponentsMgrFwd.h"
#include "ComponentLogger.h"

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sstream>

#include "HashConstructor.h"

#include "pugixml.hpp"
//
#include <lib_utils/UniStream/UniStream.h>
#include <lib_utils/UniObject/UniObject.h>
#include <lib_utils/FunctionBinder/FunctionBinder/FunctionBinder.h>
#include <lib_utils/FunctionBinder/BindableObject.h>
#include <lib_utils/GenericMsg/GenericMsg.h>
#include <lib_utils/GenericFunctionBinder/AnyStream.hpp>

//namespace pugi
//{
//    class xml_node;
//};

//

/**
 egt namespace.
 */

namespace egt {

class ComponentMgr;
class UniObject;

class IBaseComponent : public BindableObject
{
public:
    IBaseComponent() : m_componentManager(ComponentMgrWeakPtr()) {}
    virtual ~IBaseComponent(){}

    virtual void Update(){}

    bool HasContainer(const std::string& name) const;
    const CompVector& GetContainer(const std::string& name) const;
    CompVector GetContainer(const std::string& name, std::function<bool(IBaseComponentPtr)> predicate) const;

    const CompVectorContainer& GetContainers() const;
    static void AutoMergeContainers(IBaseComponentPtr lowPriorityComp, IBaseComponentPtr highPriorityComp, IBaseComponentPtr mergedCompPtr);
    static void CopyContainers(const IBaseComponent& srcComp, IBaseComponent& dstComp);

    template<typename T>
    std::vector< std::shared_ptr<T> > GetContainer(const std::string& name, std::function<bool(std::shared_ptr<T>)> predicate = nullptr) const;

    virtual std::string GetComponentName() const = 0;
    virtual IComponentId GetComponentId() const = 0;
    virtual u_int64_t GetComponentTypeHash() const = 0;
    virtual u_int64_t GetFactoryTypeHash() const = 0;
    virtual std::string GetNamespaceName() const = 0;
    virtual void Clear() = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool IsEqualTo(IBaseComponentPtr compPtr) const = 0;
    virtual void CopyFrom(const IBaseComponent* compPtr) = 0;
    virtual IBaseComponentPtr CreateCopy() const = 0;
    virtual bool Init();
    virtual void Serialize(ComponentMsgTypes::LocalMsg& msg) = 0;
    virtual void Serialize(ComponentMsgTypes::RemoteMsg& msg) = 0;
    //virtual void Deserialize(const ComponentMsgTypes::LocalMsg& msg) = 0;

    // REFLECTIONS
    struct FieldInfo
    {
        std::string fieldName;
        std::string fieldType;
        bool isRequired;
        bool isPublic;
        bool isProtected;
        bool isPrivate;
    };
    struct Field
    {
        bool isSet;
        egt::UniObject value;
    };
    class ComponentReflections
    {
    public:
        ComponentReflections( IBaseComponent& baseComp );
        std::map<std::string, IBaseComponent::FieldInfo> GetFieldsInfo() const;
        IBaseComponent::Field GetField( const std::string& fieldName ) const;
        template<typename ValueType>
        bool GetFieldValue(const std::string fieldName, ValueType& value);
        void SetField( const std::string& fieldName, const egt::UniObject& value );
        void ClearField( const std::string& fieldName );
    private:
        IBaseComponent& m_baseComponent;
    };
    friend class egt::IBaseComponent::ComponentReflections;
    ComponentReflections Reflections();
    //
    const std::string& GetComponentHint() const { return m_componentHint; }
    void SetComponentHint(const std::string& hint) { m_componentHint = hint; }

    template<class ComponentFactoryType>
    bool BaseLoad(const pugi::xml_node& xmlNode);

    template<class ComponentFactoryType>
    bool BaseLoad(iUniStream& inputStream);

    static bool ReadType(const pugi::xml_node& xmlNode, std::string& result);
    ComponentMgrPtr GetComponentManager() const;
    void SetComponentManager(ComponentMgrPtr componentManager);
    void AddToComponentVector(const std::string& vecName, IBaseComponentPtr compPtr);
    virtual bool Serialize(oUniStream& outStream) const = 0;

protected:

    static void CopyCompVector(const CompVector& src, CompVector& dst);
//    CompVector& GetContainer(const std::string& name);
    virtual bool Load(const pugi::xml_node& xmlNode) = 0;
    virtual bool Load(iUniStream& inputStream) = 0;
    virtual bool Serialize(pugi::xml_node& node) const = 0;


    template<typename T>
    static bool Read(const pugi::xml_node& xmlNode, const std::string& fieldName, T& result);

    template<typename T>
    static bool Write(pugi::xml_node xmlNode, const std::string& fieldName, const T& value);

    template<typename T>
    static  u_int64_t GetFieldHash(const char* fieldName, int fieldPos, bool isRequired);

    template<typename T>
    static  std::string GetTypeName();

private:
    static bool IsComponent(const pugi::xml_node& xmlNode);
    bool BaseSerialize(pugi::xml_node& xmlNode) const;
public:
    bool BaseSerialize(oUniStream& outStream) const;
private:
    static bool ExtractContainer(std::stringstream& src, std::stringstream& result);

    // REFLECTIONS
    virtual std::map<std::string, IBaseComponent::FieldInfo> _getFieldsInfo() const = 0;
    virtual IBaseComponent::Field _getField( const std::string& fieldName ) const = 0;
    virtual void _setField( const std::string& fieldName, const egt::UniObject& value ) = 0;
    virtual void _clearField( const std::string& fieldName ) = 0;

    ////////////////////////////////////

public:
    // UNSIGNED INT_64
    static bool ReadFromStream(std::stringstream& src, unsigned long long& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned long long& value);
    static u_int64_t GetTypeHash(const unsigned long long&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const unsigned long long&);
    // SIGNED INT_64
    static bool ReadFromStream(std::stringstream& src, signed long long& result);
    static bool WriteToStream(std::stringstream& dst, const signed long long& value);
    static u_int64_t GetTypeHash(const signed long long&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const signed long long&);
    // UNSIGNED INT_32
    static bool ReadFromStream(std::stringstream& src, unsigned long& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned long& value);
    static u_int64_t GetTypeHash(const unsigned long&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const unsigned long&);
    // SIGNED INT_32
    static bool ReadFromStream(std::stringstream& src, signed long& result);
    static bool WriteToStream(std::stringstream& dst, const signed long& value);
    static u_int64_t GetTypeHash(const signed long&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const signed long&);
    // UNSIGNED INT_16
    static bool ReadFromStream(std::stringstream& src, unsigned short& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned short& value);
    static u_int64_t GetTypeHash(const unsigned short&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const unsigned short&);
    // SIGNED INT_16
    static bool ReadFromStream(std::stringstream& src, signed short& result);
    static bool WriteToStream(std::stringstream& dst, const signed short& value);
    static u_int64_t GetTypeHash(const signed short&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const signed short&);
    // UNSIGNED INT_8
    static bool ReadFromStream(std::stringstream& src, unsigned char& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned char& value);
    static u_int64_t GetTypeHash(const unsigned char&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const unsigned char&);
    // SIGNED INT_8
    static bool ReadFromStream(std::stringstream& src, signed char& result);
    static bool WriteToStream(std::stringstream& dst, const signed char& value);
    static u_int64_t GetTypeHash(const signed char&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const signed char&);
    // UNSIGNED INT
    static bool ReadFromStream(std::stringstream& src, unsigned& result);
    static bool WriteToStream(std::stringstream& dst, const unsigned& value);
    static u_int64_t GetTypeHash(const unsigned&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const unsigned&);
    // SIGNED INT
    static bool ReadFromStream(std::stringstream& src, signed& result);
    static bool WriteToStream(std::stringstream& dst, const signed& value);
    static u_int64_t GetTypeHash(const signed&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const signed&);
    // CHAR
    static bool ReadFromStream(std::stringstream& src, char& result);
    static bool WriteToStream(std::stringstream& dst, const char& value);
    static u_int64_t GetTypeHash(const char&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const char&);
    // FLOAT
    static bool ReadFromStream(std::stringstream& src, float& result);
    static bool WriteToStream(std::stringstream& dst, const float& value);
    static u_int64_t GetTypeHash(const float&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const float&);
    // DOUBLE
    static bool ReadFromStream(std::stringstream& src, double& result);
    static bool WriteToStream(std::stringstream& dst, const double& value);
    static u_int64_t GetTypeHash(const double&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const double&);
    // STRING
    static bool ReadFromStream(std::stringstream& src, std::string& result);
    static bool WriteToStream(std::stringstream& dst, const std::string& value);
    static u_int64_t GetTypeHash(const std::string&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const std::string&);
    // BOOL
    static bool ReadFromStream(std::stringstream& src, bool& result);
    static bool WriteToStream(std::stringstream& dst, const bool& value);
    static u_int64_t GetTypeHash(const bool&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const bool&);
    // UniObject
    static bool ReadFromStream(std::stringstream& src, UniObject& result);
    static bool WriteToStream(std::stringstream& dst, const UniObject& value);
    static u_int64_t GetTypeHash(const UniObject&, u_int32_t x, u_int32_t y, u_int32_t d);
    static std::string GetTypeName(const UniObject&);
    ////////////////////////////////////
    // PAIR
    template<typename T1, typename T2>
    static bool ReadFromStream(std::stringstream& src, std::pair<T1, T2>& result);
    template<typename T1, typename T2>
    static bool WriteToStream(std::stringstream& dst, const std::pair<T1, T2>& value);
    template<typename T1, typename T2>
    static u_int64_t GetTypeHash(const std::pair<T1, T2>&, u_int32_t x, u_int32_t y, u_int32_t d);
    template<typename T1, typename T2>
    static std::string GetTypeName(const std::pair<T1, T2>&);
    // VECTOR
    template<typename T>
    static bool ReadFromStream(std::stringstream& src, std::vector<T>& result);
    template<typename T>
    static bool WriteToStream(std::stringstream& dst, const std::vector<T>& value);
    template<typename T>
    static u_int64_t GetTypeHash(const std::vector<T>&, u_int32_t x, u_int32_t y, u_int32_t d);
    template<typename T>
    static std::string GetTypeName(const std::vector<T>&);
    // MAP
    template<typename KeyT, typename ValT>
    static bool ReadFromStream(std::stringstream& src, std::map<KeyT, ValT>& result);
    template<typename KeyT, typename ValT>
    static bool WriteToStream(std::stringstream& dst, const std::map<KeyT, ValT>& value);
    template<typename KeyT, typename ValT>
    static u_int64_t GetTypeHash(const std::map<KeyT, ValT>&, u_int32_t x, u_int32_t y, u_int32_t d);
    template<typename KeyT, typename ValT>
    static std::string GetTypeName(const std::map<KeyT, ValT>&);
    ////////////////////////////////////
private:
    template<class ComponentFactoryType>
    bool ReadContainers(const pugi::xml_node& xmlNode);
    template<class ComponentFactoryType>
    bool ReadContainers(iUniStream& inputStream);


    template<class ComponentFactoryType>
    bool ReadVector(const pugi::xml_node& containerNode);
    template<class ComponentFactoryType>
    bool ReadVector(iUniStream& containerStream);

    bool WriteContainers(pugi::xml_node& xmlNode) const;
    bool WriteVector(pugi::xml_node& xmlNode, const CompVector& vec, const std::string& vecName) const;

    bool WriteContainers(oUniStream& outStream) const;
    bool WriteVector(oUniStream& outStream, const CompVector& vec, const std::string& vecName) const;

protected:

private:
    CompVectorContainer     m_vectorContainer;
    ComponentMgrWeakPtr     m_componentManager;
    std::string             m_componentHint; // some description, MUST BE USED ONLY WITH DEBUG PURPOSE

    static CompVector       m_emptyCompVector;
    static const std::string s_strXmlNodeName;
    static const std::string s_strXmlNodeType;
    static const std::string s_strXmlNodeClass;
    static const std::string s_strXmlNodeKey;
    static const std::string s_strXmlNodeCompName;
    static const std::string s_strXmlNodeCompContainer;
    static const std::string s_strXmlNodeCompMgrName;
    static const std::string s_strXmlNodeIncludeName;

    friend class ComponentMgr;
};


#include "IBaseComponent.hpp"

} // namespace egt

#endif // I_BASE_COMPONENT_
