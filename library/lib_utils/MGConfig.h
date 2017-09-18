#ifndef _MGCONFIG_H_
#define _MGCONFIG_H_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <egt_lib/utils/Color.h>
#include <project_definitions/definitions.h>
#include "MGValidate.h"


// forwards
namespace pugi
{
class xml_document;
}

/** MGConfig - multigame configuration management*/
class MGConfig
{

public:

    /** Constructor */
    MGConfig() : m_SeriesType(), m_ProductVersion() {}
    /**
     * This is common for whole project (prj)
     * */
    void SetSeriesType();
    int GetSeriesType () const ;
    const char* GetSeriesName(ESeriesVariants sType) const;
    const char* GetSeriesName() const;

    /**
     * For OLED BESEL color for different multigames ( products )
     * */
    void SetProductVersion(std::string ProductNumber);
    int GetProductVersion();

    /**
    * Init configuration
    * @param pszFilespec - fill or relative path to xml file
    * @return true on success
    */
    bool Init ( const char* pszFilespec );

    /**
    * Get integer value
    * @param pszSection - name of section
    * @param pszEntry - name of entry
    * @param [out] nValue - value of entry
    * @return true on success
    */
    bool GetInteger ( const char* pszSection, const char* pszEntry, int& nValue ) const;

    /**
    * Get string value
    * @param pszSection - name of section
    * @param pszEntry - name of entry
    * @param [out] strValue - value of entry
    * @return true on success
    */
    bool GetString ( const char* pszSection, const char* pszEntry, std::string& strValue ) const;

    /**
    * Get float value
    * @param pszSection - name of section
    * @param pszEntry - name of entry
    * @param [out] nValue - value of entry
    * @return true on success
    */
    bool GetFloat(const char* pszSection, const char* pszEntry, float& nValue) const;

    /**
    * Get bool value
    * @param pszSection - name of section
    * @param pszEntry - name of entry
    * @param [out] nValue - value of entry
    * @return true on success
    */
    bool GetBool(const char* pszSection, const char* pszEntry, bool& nValue) const;

    struct GameDesc {
        GameDesc() : m_uGameId(), m_uPosition() {}
        unsigned m_uGameId;
        unsigned m_uPosition;
        std::string m_strLibso;
        std::string m_strSfLibso;
        std::string m_strName;
        std::string m_strType;
        std::string m_strSubType;
    };

    /**
    * Get description of games
    * @param [out] vecGames - vector games
    * @return true on success
    */
    bool GetGames ( std::vector<GameDesc>& vecGames ) const;

    /**
    * Get jurisdictions
    * @param [out] mapJurisdictions - map of jurisdictions - pair { id, jurisdiction }
    * @return true on success
    */
    bool GetJurisdictions ( std::map<unsigned, std::string>& mapJurisdictions ) const;

    /// Get the product, series, and full name of the product
    ///	@param series - the series identifier
    ///	@param product - the product identifier
    ///	@param name - the full name of the product
    ///	@return true if identifiers were successfully extracted from multigame.xml
    bool GetProduct ( std::string& series, std::string& product, std::string& name ) const;

    struct DemoEvent {
        DemoEvent() : mName(), mValue() {}
        std::string mName;
        unsigned mValue;
    };

    bool GetDemoSequence ( std::vector<DemoEvent>& vecSequence ) const;


    //////////////////////////////////

    struct SecondScreenResourcesData {
            std::string value;
            std::string name;

            SecondScreenResourcesData() : value(), name() {}
            SecondScreenResourcesData(std::string  m_value, std::string nm) : value(m_value), name(nm) {}
        };

    bool GetSecondScreenResourcesValues(std::vector<SecondScreenResourcesData> &vSecondScrData);

    struct SeriesPowerGameVariantsData {
         int GameID;
         int GameVariantInex;

            SeriesPowerGameVariantsData() : GameID(), GameVariantInex() {}
            SeriesPowerGameVariantsData(unsigned int  m_Game_ID, unsigned int GameVarIdx) : GameID(m_Game_ID), GameVariantInex(GameVarIdx) {}
           };

     bool GetPowerGameVariantsValues(std::vector<SeriesPowerGameVariantsData> &vPowerGamesData);


     /** xml document */
     std::shared_ptr<pugi::xml_document> m_spxmlDoc;

private:



    int m_SeriesType;
    int m_ProductVersion;
};

extern MGConfig gMGCfg;

#endif // _MGCONFIG_H_
