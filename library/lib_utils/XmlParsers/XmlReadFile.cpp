#include "XmlReadFile.h"

#include "pugixml.hpp"
#include <egt_lib/debug/egt_debug.h>
#include <iostream>
#include <algorithm>
#include "../MGValidate.h"

#define LOG eCDebug(LOG_CATEGORY_LIBS)


// XML constants
static const std::string& g_strXmlNodeConfig 	= MGValidate::GetItem ( MGValidate::XML_NODE_CONFIG );
static const std::string& g_strXmlNodeGames 		= MGValidate::GetItem ( MGValidate::XML_NODE_GAMES );
static const std::string& g_strXmlNodeGame 		= MGValidate::GetItem ( MGValidate::XML_NODE_GAME );
static const std::string& g_strXmlNodePair 		= MGValidate::GetItem ( MGValidate::XML_NODE_PAIR );
static const std::string& g_strXmlNodeJurisdiction = MGValidate::GetItem ( MGValidate::XML_NODE_JURISDICTION );
static const std::string& g_strXmlNodeVersion 	= MGValidate::GetItem ( MGValidate::XML_NODE_VERSION );
static const std::string& g_strXmlNodeEvent 		= MGValidate::GetItem ( MGValidate::XML_NODE_EVENT );
static const std::string& g_strXmlNodeDevice 		= MGValidate::GetItem ( MGValidate::XML_NODE_DEVICE );
static const std::string& g_strXmlNodeOledColorBesel	= MGValidate::GetItem ( MGValidate::XML_NODE_OLED_COLOR_BESEL );
static const std::string& g_strXmlNodeBlink	= MGValidate::GetItem ( MGValidate::XML_NODE_BLINK );
static const std::string& g_strXmlNodeInclude = MGValidate::GetItem ( MGValidate::XML_NODE_INCLUDE );
static const std::string& g_strXmlNodeParameter = MGValidate::GetItem ( MGValidate::XML_NODE_PARAMETER );

static const std::string& g_strXmlAttrName 		= MGValidate::GetItem ( MGValidate::XML_ATTR_NAME );
static const std::string& g_strXmlAttrSeries 	= MGValidate::GetItem ( MGValidate::XML_ATTR_SERIES );
static const std::string& g_strXmlAttrProduct 	= MGValidate::GetItem ( MGValidate::XML_ATTR_PRODUCT );
static const std::string& g_strXmlAttrValue 		= MGValidate::GetItem ( MGValidate::XML_ATTR_VALUE );
static const std::string& g_strXmlAttrId 			= MGValidate::GetItem ( MGValidate::XML_ATTR_ID );
static const std::string& g_strXmlAttrType 		= MGValidate::GetItem ( MGValidate::XML_ATTR_TYPE );
static const std::string& g_strXmlAttrSubType 	= MGValidate::GetItem ( MGValidate::XML_ATTR_SUBTYPE );
static const std::string& g_strXmlAttrPosition 	= MGValidate::GetItem ( MGValidate::XML_ATTR_POSITION );
static const std::string& g_strXmlAttrAllowed 	= MGValidate::GetItem ( MGValidate::XML_ATTR_ALLOWED );
static const std::string& g_strXmlAttrColor 	= MGValidate::GetItem ( MGValidate::XML_ATTR_COLOR );
static const std::string& g_strXmlAttrTime	= MGValidate::GetItem ( MGValidate::XML_ATTR_TIME );



static const std::string& g_strXmlAllowedYes 	= MGValidate::GetItem ( MGValidate::XML_ALLOWED_YES );
static const std::string& g_strXmlEntrySep 		= MGValidate::GetItem ( MGValidate::XML_ENTRY_SEP );



XmlReadFile::XmlReadFile()
{

}

XmlReadFile::~XmlReadFile()
{

}

bool XmlReadFile::Init ( const char* pszFilespec )
{
    m_spxmlDoc.reset ( new pugi::xml_document() );

    pugi::xml_parse_result result = m_spxmlDoc->load_file ( pszFilespec, pugi::parse_default | pugi::parse_pi );

    if ( !result )
    {

        LOG << "XML Error description: " << result.description();
        LOG << "XML Error offset: " << result.offset << "]\n";

        return false;
    }

    return true;

}

static bool GetEntryNode ( pugi::xml_document* pDoc, const char* pszSection, const char* pszEntry, pugi::xml_node& node_entry )
{

    if ( nullptr == pszSection || nullptr == pszEntry || nullptr == pDoc )
    {
        return false;
    }

    std::string strKey = pszSection;
    strKey += g_strXmlEntrySep;
    strKey += pszEntry;

    pugi::xpath_node_set xset = pDoc->select_nodes ( "//*" ); // traverse all nodes, TODO: use xpath
    for ( pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it )
    {

        pugi::xml_node node = it->node();

        if ( g_strXmlNodePair == node.name() )
        {

            std::string strName = node.attribute ( g_strXmlAttrName.c_str() ).as_string();
            if ( strName == strKey )
            {

                node_entry = node;
                return true;
            }
        }
    }

    return false;
}


bool XmlReadFile::GetInteger ( const char* pszSection, const char* pszEntry, int& nValue ) const
{

    pugi::xml_node node;
    if ( GetEntryNode ( m_spxmlDoc.get(), pszSection, pszEntry, node ) )
    {

        nValue = node.attribute ( g_strXmlAttrValue.c_str() ).as_int();
        return true;
    }

    return false;
}

bool XmlReadFile::GetFloat ( const char* pszSection, const char* pszEntry, float& nValue ) const
{

    pugi::xml_node node;
    if ( GetEntryNode ( m_spxmlDoc.get(), pszSection, pszEntry, node ) )
    {

        nValue = node.attribute ( g_strXmlAttrValue.c_str() ).as_float();
        return true;
    }

    return false;
}


bool XmlReadFile::GetBool ( const char* pszSection, const char* pszEntry, bool& nValue ) const
{

    pugi::xml_node node;
    if ( GetEntryNode ( m_spxmlDoc.get(), pszSection, pszEntry, node ) )
    {

        nValue = node.attribute ( g_strXmlAttrValue.c_str() ).as_bool();
        return true;
    }

    return false;
}

bool XmlReadFile::GetString ( const char* pszSection, const char* pszEntry, std::string& strValue ) const
{

    pugi::xml_node node;
    if ( GetEntryNode ( m_spxmlDoc.get(), pszSection, pszEntry, node ) )
    {

        strValue = node.attribute ( g_strXmlAttrValue.c_str() ).as_string();
        return true;
    }

    return false;
}

