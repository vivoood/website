#ifndef _MGVALIDATE_H_
#define _MGVALIDATE_H_

#include <vector>
#include <string>

// forwards
namespace pugi { class xml_document; }

/** MGValidate - multigame configuration validate*/
class MGValidate {

public:

	/**
	* Init configuration
	* @param pszFilespec - fill or relative path to xml file
	* @return true on success
	*/
	bool Init(const char* pszFilespec);


    /**
    * ValidateWithLibXML
    * @brief Validates XML file for basic tag mismaches
    * @param xmlFilePath - Full path to xml file
    * @return true on success
    */
    static bool ValidateWithLibXML(const std::string& xmlFilePath);


	enum EXmlItem {
		XML_FIRST_ITEM,
		XML_NODE_INCLUDE,
		XML_NODE_PARAMETER,
		XML_NODE_GAMES,
		XML_NODE_GAME,
		XML_NODE_AREA,
		XML_NODE_CONFIG,
		XML_NODE_PAIR,
		XML_NODE_JURISDICTION,
		XML_NODE_VERSION,
		XML_NODE_EVENT,
		XML_NODE_DEVICE,
		XML_NODE_OLED_COLOR_BESEL,
		XML_NODE_BLINK,
		XML_NODE_PHASE,
        XML_NODE_COMPMGR,
        XML_NODE_COMPONENT,
        XML_NODE_COMP_CONTAINER,
        XML_NODE_NVRAM,

		XML_ATTR_NAME,
		XML_ATTR_SERIES,
		XML_ATTR_PRODUCT,
		XML_ATTR_VALUE,
		XML_ATTR_SIZE,
		XML_ATTR_ADDRESS,
		XML_ATTR_ID,
		XML_ATTR_TYPE,
		XML_ATTR_SUBTYPE,
		XML_ATTR_POSITION,
		XML_ATTR_ALLOWED,
		XML_ATTR_DATASIZE,
		XML_ATTR_COUNT,
		XML_ATTR_VERIFY,
		XML_ATTR_DEFAULT,
		XML_ATTR_REF,
		XML_ATTR_MASK,
		XML_ATTR_TRIGGERLOG,
		XML_ATTR_DESCRIPTION,
		XML_ATTR_COLOR,
		XML_ATTR_TIME,
		XML_ATTR_SEGMENT,
        XML_ATTR_KEY,
        XML_ATTR_TAGNAME,
        XML_ATTR_FILENAME,
        XML_ATTR_CLASS,
		XML_ATTR_DIR,
		XML_ATTR_TARGET_NAME,

		XML_TYPE_GAMESTATUNIT,
		XML_TYPE_ARRAY,
		XML_TYPE_CRC,
		XML_TYPE_LOCK,
		
		XML_VERIFY_ALL,
		XML_DEFAULT_MAX,
		XML_DEFAULT_CURR_TIME,
		XML_DEFAULT_NOLIMIT,
		XML_ALLOWED_YES,
		XML_ENTRY_SEP,
		XML_LAST_ITEM
	};

	static const char* GetItem(EXmlItem item);

private:
	bool ValidateXmlFile(const char* pszFilespec, pugi::xml_document& dom);

	bool ValidateDuplicatedParameter(pugi::xml_document& dom);

	bool ValidateParameterAttributes(pugi::xml_document& dom);

	bool ValidateGames(const char* pszFilespec);

    void UpdateGameIDs(unsigned uId, std::vector<unsigned> &vectorGameIDs);
};

#endif // _MGVALIDATE_H_
