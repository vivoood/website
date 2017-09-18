#include "XmlGameFile.h"
#include "../MGValidate.h"
#include "pugixml.hpp"
#include <iostream>
#include <egt_lib/debug/egt_debug.h>

#include <sstream>

static const std::string& g_strXmlNodeParameter = MGValidate::GetItem ( MGValidate::XML_NODE_PARAMETER );
static const std::string& g_strXmlAttrName 		= MGValidate::GetItem ( MGValidate::XML_ATTR_NAME );


XmlGameFile::XmlGameFile()
{

}

XmlGameFile::~XmlGameFile()
{

}

bool XmlGameFile::GetLanguages ( std::vector< std::string >& vLanguages ) const
{
    if ( m_spxmlDoc.get() == nullptr )
    {
        return false;
    }
    std::string strLang;

    pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ( "//*" ); // traverse all nodes
    for ( auto it = xset.begin(); it != xset.end(); ++it )
    {

        pugi::xml_node node = it->node();

        if ( g_strXmlNodeParameter == node.name() )
        {

            std::string strName = node.attribute ( g_strXmlAttrName.c_str() ).as_string();

            if ( strName == "Languages" )
            {

                strLang = node.attribute ( "value" ).as_string();

                break;
            }


        }
    }

    //split

    std::stringstream ss ( strLang );
    std::string buf; // Have a buffer string
    while ( ss >> buf )
    {
        vLanguages.push_back ( buf );
    }

    return  ! strLang.empty();
}

/*
void XmlGameFile::EXTRACT_GAMES(std::map<int, std::string>& outMap)
{
    pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ( "/multigame/config/games/game" ); // traverse all nodes

    for ( auto it = xset.begin(); it != xset.end(); ++it )
    {
        pugi::xml_node node = it->node();
        int id = node.attribute("id").as_int();
        auto dir = node.attribute("dir").as_string();
        outMap[id] = dir;
    }
}

void XmlGameFile::DBG_DELETE_ME_DO_MULTIGAME_TEST()
{
    if (!Init("../series_test/multigame-all/multigame.xml"))
    {
        int debuggg = 34;
    }
    std::map<int, std::string> mainMap;

    EXTRACT_GAMES(mainMap);

    std::vector<XmlGameFile> xmls;
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_collection/product_one/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_collection/product_two/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_collection/product_three/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_collection_4/product_green/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_collection_4/product_red/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_collection_6/product_orange/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_collection_6/product_purple/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_power/product_one/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_power/product_red/multigame.xml");
    //
    xmls.push_back(XmlGameFile());
    xmls.back().Init("../series_4HappyHits/product_one/multigame.xml");

    std::map<int, std::string> allXmls;
    for(auto& xml : xmls)
    {
        xml.EXTRACT_GAMES(allXmls);
    }

    std::vector<std::pair<int, std::string>> missing;

    for(auto& p : allXmls)
    {
        int id = p.first;
        auto iter = mainMap.find(id);
        if (iter == mainMap.end())
        {
            //eCDebug(LOG_CATEGORY_LIBS) << p.second << "\n";
            missing.push_back(p);
        }
    }

    for(auto& mName : missing)
    {
        for(int i = 0; i < xmls.size(); i++)
        {
            std::map<int, std::string> tmp;
            xmls[i].EXTRACT_GAMES(tmp);
            auto it = tmp.find(mName.first);
            if (it != tmp.end())
            {
                eCDebug(LOG_CATEGORY_LIBS) << mName.second << " " << i << "\n";
            }
        }
    }


    int sz = allXmls.size();
    eCDebug(LOG_CATEGORY_LIBS) << sz << "\n";
}
*/
