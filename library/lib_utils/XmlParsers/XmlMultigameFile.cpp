#include "XmlMultigameFile.h"
#include "../MGValidate.h"
#include "pugixml.hpp"

static const std::string& g_strXmlNodeGame = MGValidate::GetItem ( MGValidate::XML_NODE_GAME );
static const std::string& g_strXmlNodeArea = MGValidate::GetItem ( MGValidate::XML_NODE_AREA );
static const std::string& g_strXmlNodeInclude = MGValidate::GetItem ( MGValidate::XML_NODE_INCLUDE );


static const std::string& g_strXmlAttrId = MGValidate::GetItem ( MGValidate::XML_ATTR_ID );

XmlMultigameFile::XmlMultigameFile()
{

}

XmlMultigameFile::~XmlMultigameFile()
{

}



bool XmlMultigameFile::ReadGamesPath ( std::map< unsigned, std::string >& mGamesPath )
{
    /*
      <nvram>
        <area id="HEADER"> <include> ./header.xml </include> </area>
        <area id="MAIN"> <include> ./general.xml </include> </area>
        <area id="GAMES">
        <!-- Common Page 1 -->
            <game id="147"> <include> ./hybrid.xml </include>  <include segment= "NVRAM"> ./thumbelina_dream.xml </include> </game>

      */

    if ( m_spxmlDoc.get() == nullptr )
    {
        return false;
    }

    for (const auto it : m_spxmlDoc->select_nodes ( "//nvram/*" ))
    {
        CheckNode(it.node(), mGamesPath);
    }

    return ! mGamesPath.empty();
}

void XmlMultigameFile::CheckNode(const pugi::xml_node& node, std::map<unsigned, std::string> & mGamesPath)
{
    unsigned gameId = node.attribute ( "id" ).as_uint();

    bool ok = false;
    if ( g_strXmlNodeGame == node.name() && gameId != 0 )
    {
        for (const auto& nodeInclude : node.children())
        {
            if (nodeInclude.attribute ( "segment" ).empty())
            {
                continue;
            }

            if ( nodeInclude.name() == g_strXmlNodeInclude )
            {
                std::string strFile = nodeInclude.first_child().value();
                mGamesPath.insert ( std::pair<unsigned, std::string> ( gameId,strFile ) );
                ok = true;
                break;
            }
        }
    }

    if (!ok)
    {
        for(const auto& child : node.children())
        {
            CheckNode(child, mGamesPath);
        }
    }
}

