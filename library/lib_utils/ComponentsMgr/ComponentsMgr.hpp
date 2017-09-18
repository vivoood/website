///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool ComponentMgr::AddXmlNode(const pugi::xml_node& xmlNode, const std::string& hint)
{
    if (AddComponent<ComponentFactoryType>(xmlNode, hint))
    {
    }
    else if (AddIncludeFile<ComponentFactoryType>(xmlNode))
    {
    }
    else
    {
        COMP_MGR_LOG << "Unknown xml node: " << xmlNode.name();
        return false;
    }
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool ComponentMgr::AddComponent(const pugi::xml_node& xmlNode, const std::string& hint)
{
    if (false == IBaseComponent::IsComponent(xmlNode))
    {
        return false;
    }

    auto comp = ComponentFactoryType::CreateComponent(xmlNode);
    if (nullptr == comp)
    {
        COMP_MGR_LOG << "Error creating component from xml node: " << xmlNode.name();
        return false;
    }
    comp->SetComponentHint(hint);

    if( m_components.find(comp->GetComponentId()) == m_components.end())
    {
        m_components[comp->GetComponentId()] = comp;
        return true;
    }
    COMP_MGR_LOG << "Duplicate component: " << comp->GetComponentName() << ", hint : " << comp->GetComponentHint();
    return false;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool ComponentMgr::InitMgr()
{
    m_autoMerge = &(ComponentFactoryType::AutoMerge);

    m_factoryHash = ComponentFactoryType::GetFactoryHash();
    return true;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
ComponentMgrPtr ComponentMgr::CreateEmptyMgr(const std::string& mgrName)
{
    ComponentMgrPtr ptr = std::make_shared< ComponentMgr >();
    ptr->m_name = mgrName;
    if (false == ptr->InitMgr<ComponentFactoryType>())
    {
        return nullptr;
    }
    return ptr;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool ComponentMgr::LoadFromXmlNode(const pugi::xml_node& xmlNode, std::string hint)
{
    //xmlNode.na
    try
    {
        if (false == IsManager(xmlNode))
        {
            auto name = GetName();

            COMP_MGR_LOG << "Invalid Component Manager Node : " << name;
            return false;
        }
        const auto& nameAttr = xmlNode.attribute ( s_strXmlAttrName.c_str() );
        m_name = nameAttr.as_string();

        for (const auto& childNode : xmlNode.children())
        {
            if (false == AddXmlNode<ComponentFactoryType>(childNode, hint))
            {
                auto name = GetName();

                COMP_MGR_LOG << "Invalid Component Node in " << name << " -> ";
                return false;
            }
        }
    }
    catch(int& e)
    {
        auto name = GetName();

        COMP_MGR_LOG << "Exception in " << name;
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool ComponentMgr::AddIncludeFile(const pugi::xml_node& xmlNode)
{
    if (s_strXmlNodeInclude != xmlNode.name())
    {
        return false;
    }

    const auto& fileNameAttr = xmlNode.attribute(s_strXmlAttrFileName.c_str());
    if (fileNameAttr.empty())
    {
        COMP_MGR_LOG << "Not set " << s_strXmlAttrFileName << " attribute.";
        COMP_ASSERT("");
        return false;
    }

    const auto& tagAttr = xmlNode.attribute(s_strXmlAttrTagName.c_str());
    const auto& segmentAttr = xmlNode.attribute(s_strXmlAttrSegment.c_str());

    std::stringstream pugiQueryStream;
    if (!tagAttr.empty())
    {
        pugiQueryStream << tagAttr.as_string();
    }
    else
    {
        pugiQueryStream << "*";

    }

    if (!segmentAttr.empty())
    {
        pugiQueryStream << "[@segment='" << segmentAttr.as_string() << "']";
    }

    std::string strFile = std::string(fileNameAttr.as_string());

    //auto iss = std::isspace;
    auto it = remove_if(strFile.begin(), strFile.end(), [](char c){
        return std::isspace(static_cast<unsigned char>(c));
     });

    strFile.erase(it, strFile.end());

    pugi::xml_document spxmlDoc;
    bool result = LoadXML(strFile, spxmlDoc, pugi::parse_default | pugi::parse_pi);
    if ( !result )
    {
        return false;
    }

    std::string query  = pugiQueryStream.str();
    for (const auto it : spxmlDoc.select_nodes (query.c_str()))
    {
        for (const auto node : it.node().select_nodes("*"))
        {
            const auto& incNode = node.node();
            if (false == AddXmlNode<ComponentFactoryType>(incNode, strFile))
            {
                auto name = GetName();

                COMP_MGR_LOG << "Invalid Component Node in file : " << strFile;
                COMP_ASSERT("");
                return false;
            }
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////
template <typename T>
std::shared_ptr<T> ComponentMgr::GetComponent() const
{
    IBaseComponentPtr baseCompPtr = GetComponent( T::GetComponentIdStatic() );

    if( nullptr == baseCompPtr)
    {
        return nullptr;
    }
    return T::SafeCast( baseCompPtr );
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
ComponentMgrPtr ComponentMgr::CreateFromFile (const std::string& fileName, const std::string& mgrName)
{
    ComponentMgrPtr ptr = ComponentMgr::CreateMgr();

    if (nullptr == ptr)
    {
        COMP_ASSERT("Cant create component mgr.");
        return nullptr;
    }
    ptr->InitMgr<ComponentFactoryType>();
    ptr->m_name = mgrName;

    if (ptr->LoadFromFile<ComponentFactoryType>(fileName))
    {
        IntroduceManagerToAllComponents(ptr);
        return ptr;
    }

    COMP_MGR_LOG << "Error creating from file : " << fileName << " ; mgrName : " << mgrName;
    COMP_ASSERT("Cant init component mgr.");

    return nullptr;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
bool ComponentMgr::LoadFromFile (const std::string& fileName)
{
    pugi::xml_document spxmlDoc;
    bool result = LoadXML(fileName, spxmlDoc, pugi::parse_default | pugi::parse_pi);
    if ( !result )
    {
        return false;
    }

    pugi::xml_node mainNode;
    pugi::xpath_node_set xset = spxmlDoc.select_nodes ( "//*" ); // traverse all nodes
    pugi::xml_node rootNode = xset.begin()->node();
    if (rootNode.name() == std::string("Root"))
    {
        xset = spxmlDoc.select_nodes ( "//Roor/*" ); // traverse all nodes
    }
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
        if (m_name != nameAttribute.as_string())
        {
            continue;
        }

        mainNode = node;
        break;
    }

    if (mainNode.empty())
    {
        COMP_MGR_LOG << "Cant find start mgr node : " << fileName << " ; mgrName : " << m_name;
        COMP_ASSERT("");
        return false;
    }

    if (LoadFromXmlNode<ComponentFactoryType>(mainNode, fileName))
    {
        return true;
    }

    COMP_MGR_LOG << "Error parsing file : " << fileName << " ; mgrName : " << m_name;
    COMP_ASSERT("Cant load component mgr.");
    return false;
}

///////////////////////////////////////////////////////////////////////////
template<class ComponentFactoryType>
ComponentMgrPtr ComponentMgr::CreateFromStream(iUniStream& inpStream)
{
    iUniStream mgrStream;

    if (!(inpStream >> iUniInplace(mgrStream)))
    {
        COMP_MGR_LOG << "Cant extract Component Manager stream.";
        return nullptr;
    }

    std::string mgrName;
    if (!(mgrStream >> mgrName))
    {
        COMP_MGR_LOG << "Cant extract Component Manager name.";
        return nullptr;
    }

    iUniStream componentsStream;

    if (!(mgrStream >> iUniInplace(componentsStream)))
    {
        COMP_MGR_LOG << "Cant extract components stream : " << mgrName;
        return nullptr;
    }

    ComponentMgrPtr ptr = ComponentMgr::CreateMgr();
    ptr->m_name = mgrName;
    if (false == ptr->InitMgr<ComponentFactoryType>())
    {
        return nullptr;
    }

    while(!componentsStream.IsEmpty())
    {
        auto comp = ComponentFactoryType::CreateComponent(componentsStream);
        if (nullptr == comp)
        {
            COMP_MGR_LOG << "Error parsing components in component manager : " << mgrName;
            return nullptr;
        }
        if( ptr->m_components.find(comp->GetComponentId()) == ptr->m_components.end())
        {
            ptr->m_components[comp->GetComponentId()] = comp;
        }
        else
        {
            COMP_MGR_LOG << "Duplicate component in manager : " << mgrName << " / " << comp->GetComponentName();
            return nullptr;
        }
    }
    IntroduceManagerToAllComponents(ptr);
    return ptr;
}
