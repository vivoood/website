#include "MGValidate.h"
#include "pugixml.hpp"
#include <string>
#include <algorithm>
#include <stdarg.h>
#include <libxml/xmlschemas.h>
#include <map>

// xml constants
static const std::string& g_strXmlNodeInclude = MGValidate::GetItem(MGValidate::XML_NODE_INCLUDE);
static const std::string& g_strXmlNodeParameter = MGValidate::GetItem(MGValidate::XML_NODE_PARAMETER);
static const std::string& g_strXmlNodeGames = MGValidate::GetItem(MGValidate::XML_NODE_GAMES);
static const std::string& g_strXmlNodeGame = MGValidate::GetItem(MGValidate::XML_NODE_GAME);
static const std::string& g_strXmlNodeConfig = MGValidate::GetItem(MGValidate::XML_NODE_CONFIG);
static const std::string& g_strXmlNodeNvram = MGValidate::GetItem(MGValidate::XML_NODE_NVRAM);
static const std::string& g_strXmlAttrId = MGValidate::GetItem(MGValidate::XML_ATTR_ID);
static const std::string& g_strXmlAttrName = MGValidate::GetItem(MGValidate::XML_ATTR_NAME);
static const std::string& g_strXmlAttrType = MGValidate::GetItem(MGValidate::XML_ATTR_TYPE);
static const std::string& g_strXmlAttrSize = MGValidate::GetItem(MGValidate::XML_ATTR_SIZE);
static const std::string& g_strXmlAttrDatasize = MGValidate::GetItem(MGValidate::XML_ATTR_DATASIZE);
static const std::string& g_strXmlAttrCount = MGValidate::GetItem(MGValidate::XML_ATTR_COUNT);
static const std::string& g_strTypeArray = MGValidate::GetItem(MGValidate::XML_TYPE_ARRAY);
static const std::string& g_strTypeLock = MGValidate::GetItem(MGValidate::XML_TYPE_LOCK);
static const std::string& g_strTypeGameStatUnit = MGValidate::GetItem(MGValidate::XML_TYPE_GAMESTATUNIT);

static const char* g_arrItems[ MGValidate::XML_LAST_ITEM ] = {
    "XML_UNKNOWN_ITEM"
	//nodes
	, "include"
	, "parameter"
	, "games"
	, "game"
	, "area"
	, "config"
	, "pair"
	, "jurisdiction"
	, "version"
	, "event"
	, "device"
	, "oledColorBesel"
	, "blink"
	, "phase"
    , "compmgr"
    , "component"
    , "compcontainer"
    , "nvram"
	
	//attributes
	, "name"
	, "series"
	, "product"
	, "value"
	, "size"
	, "address"
	, "id"
	, "type"
	, "subtype"
	, "position"
	, "allowed"
	, "datasize"
	, "count"
	, "verify"
	, "default"
	, "ref"
	, "mask"
	, "triggerlog"
	, "description"
	, "color"
	, "time"
	, "segment"
    , "key"
    , "tagname"
    , "filename"
    , "class"
	, "dir"
	, "target_name"
	
	//types
	, "gamestatunit"
	, "array"
	, "crc"
	, "lock"
	, "all"
	//Defaults
	, "dfv_max"
	, "dfv_curr_time"
	, "dfv_nolimit"
	//flag
	, "yes"
	//separator
	, "."
	
};


bool MGValidate::Init(const char* pszFilespec) {

	pugi::xml_document dom;

	return (ValidateXmlFile(pszFilespec, dom) &&
            ValidateGames(pszFilespec));
}


namespace {

void structuredErrorHandler(void *, xmlErrorPtr error)
{
    std::string errorLevel = [error]()
    {
        switch( error->level )
        {
            case XML_ERR_WARNING: return "\033[0;93mXML WARNING\033[0m";
            case XML_ERR_ERROR: return "\033[0;91mXML ERROR\033[0m";
            case XML_ERR_FATAL: return "\033[0;91mXML FATAL\033[0m";
            default : return " ";
        }
    }();

//     eCDebug(LOG_CATEGORY_LIBS) << errorLevel << " [" << error->code << "]: " // You can find the meaning of an error number in xmlerror.h in libxml2
//                                << ((error->file != nullptr) ? error->file : "nullptr") << " Line: " << error->line << ": " << error->message;
}

}

bool MGValidate::ValidateWithLibXML(const std::string &xmlFilePath)
{
    xmlDocPtr doc;

    xmlSetStructuredErrorFunc(NULL, structuredErrorHandler);

    doc = xmlReadFile(xmlFilePath.c_str(), NULL, 0);
    if (doc == NULL)
    {
        return false;
    }

    xmlFreeDoc(doc);

    return true;
}

const char* MGValidate::GetItem(EXmlItem item) {

	if (item < XML_LAST_ITEM) return g_arrItems[ item ];
	else return g_arrItems[ XML_FIRST_ITEM ];
}

bool MGValidate::ValidateXmlFile(const char* pszFilespec, pugi::xml_document& dom) {

	pugi::xml_parse_result result = dom.load_file(pszFilespec, pugi::parse_default | pugi::parse_pi);

	if (!result) {

// 		eCDebug(LOG_CATEGORY_LIBS) << "Failed to load " << pszFilespec <<" : " << result.description() << ": error at " << result.offset;
		return false;
	}

	pugi::xpath_node_set xset = dom.select_nodes("//*"); // traverse all nodes, TODO: use xpath
	for (pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it) {

		pugi::xml_node node = it->node();

		if (g_strXmlNodeInclude == node.name()) {

			std::string path = node.value();

			if (path.empty()) {

				path = node.first_child().value();
			}

			path.erase(std::remove(path.begin(), path.end(), ' '), path.end());
			if (!path.empty()) {

				if (! Init(path.c_str())) return false;
			}
		}
	}

	return (ValidateDuplicatedParameter(dom) &&
			ValidateParameterAttributes(dom));
}

bool MGValidate::ValidateDuplicatedParameter(pugi::xml_document& dom) {

	std::map<std::string, unsigned> mapNames;
	pugi::xpath_node_set xset = dom.select_nodes("//*"); // traverse all nodes, TODO: use xpath
	for (pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it) {

		pugi::xml_node node = it->node();

		if (g_strXmlNodeParameter == node.name()) {

			std::string strName = node.attribute(g_strXmlAttrName.c_str()).as_string();
			auto it = mapNames.find(strName);
			if (mapNames.end() == it) {
				mapNames[ strName ] = 1;
			} else {
				it->second ++;
			}
		}
	}

	bool bDuplicated = false;
	for (auto it = mapNames.begin(); mapNames.end() != it; it ++) {

		if (it->second > 1) {
			bDuplicated = true;
// 			eCDebug(LOG_CATEGORY_LIBS) << "Nvram parameter" << it->first.c_str() << "is repeated " << it->second << "times!!!";
		}
	}

	return !bDuplicated;
}

bool MGValidate::ValidateParameterAttributes(pugi::xml_document& dom) {

	std::map<std::string, unsigned> mapNames;
	pugi::xpath_node_set xset = dom.select_nodes("//*"); // traverse all nodes, TODO: use xpath
	for (pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it) {

		pugi::xml_node node = it->node();

		if (g_strXmlNodeParameter == node.name()) {

			std::string strName = node.attribute(g_strXmlAttrName.c_str()).as_string();
			std::string strType = node.attribute(g_strXmlAttrType.c_str()).as_string();
			unsigned uSize = node.attribute(g_strXmlAttrSize.c_str()).as_int();

			if (g_strTypeArray == strType) {

				if (0 == uSize) {

					uSize = node.attribute(g_strXmlAttrDatasize.c_str()).as_int() * node.attribute(g_strXmlAttrCount.c_str()).as_int();
				}

			} else if ((g_strTypeGameStatUnit == strType) || (g_strTypeLock == strType)) {

				uSize = ~0; // there is a default size
			}

			if (0 == uSize) {

				mapNames[ strName ] = 1;
			}
		}
	}

	bool bInvalid = false;
	for (auto it = mapNames.begin(); mapNames.end() != it; it ++) {

		if (it->second > 0) {
			bInvalid = true;
//             eCDebug(LOG_CATEGORY_LIBS) << "Nvram parameter" << it->first.c_str() << " is not specified (unknown size of data)!!!\n";
		}
	}

    return !bInvalid;
}

bool MGValidate::ValidateGames(const char* pszFilespec) {

	bool bRet = false;
	pugi::xml_document dom;
	pugi::xml_parse_result result = dom.load_file(pszFilespec, pugi::parse_default | pugi::parse_pi);

    if(!result)
    {
// 		eCDebug(LOG_CATEGORY_LIBS) << "Failed to load" << pszFilespec <<" : "<< result.description() << ": error at " << result.offset;
    }
    else
    {
		bRet = true;
        std::vector<unsigned> vectorGamesInConfig;
        std::vector<unsigned> vectorGamesInNvram;
		pugi::xpath_node_set xset = dom.select_nodes("//*"); // traverse all nodes, TODO: use xpath
        for (pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it)
        {

			pugi::xml_node node = it->node();

            if (g_strXmlNodeGame != node.name())
            {
                continue;
            }

            unsigned uId = node.attribute(g_strXmlAttrId.c_str()).as_int();
            if (0 != uId)
            {
                if (g_strXmlNodeConfig == node.parent().parent().name())
                {
                    UpdateGameIDs(uId, vectorGamesInConfig);
                    continue;
                }

                if (g_strXmlNodeNvram == node.parent().parent().name())
                {
                    UpdateGameIDs(uId, vectorGamesInNvram);
                }
			}
		}

        for (auto itConfig = vectorGamesInConfig.begin(); vectorGamesInConfig.end() != itConfig; itConfig ++)
        {
            auto itNvram = std::find(vectorGamesInNvram.begin(), vectorGamesInNvram.end(), *itConfig);

            if(itNvram == vectorGamesInNvram.end())
            {
                bRet = false;
//                 eCDebug(LOG_CATEGORY_LIBS) << "Game id = " << *itConfig << " not found in nvram sections, file = " << pszFilespec << "!!!\n";
            }
		}
	}

	return bRet;
}

void MGValidate::UpdateGameIDs(unsigned uId, std::vector<unsigned> &vectorGameIDs)
{
    auto it = std::find(vectorGameIDs.begin(), vectorGameIDs.end(), uId);

    if(it == vectorGameIDs.end())
    {
        vectorGameIDs.push_back(uId);
    }
}
