#include "MGConfig.h"
#include "MGValidate.h"
#include "pugixml.hpp"
#include <egt_lib/debug/egt_debug.h>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>


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
static const std::string& g_strXmlNodeInclude = MGValidate::GetItem(MGValidate::XML_NODE_INCLUDE);

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
static const std::string& g_strXmlAttrDir	= MGValidate::GetItem ( MGValidate::XML_ATTR_DIR );
static const std::string& g_strXmlAttrTargetName = MGValidate::GetItem ( MGValidate::XML_ATTR_TARGET_NAME );



static const std::string& g_strXmlAllowedYes 	= MGValidate::GetItem ( MGValidate::XML_ALLOWED_YES );
static const std::string& g_strXmlEntrySep 		= MGValidate::GetItem ( MGValidate::XML_ENTRY_SEP );

bool MGConfig::Init ( const char* pszFilespec )
{

    m_SeriesType = 0;
    m_ProductVersion = 0;

    //if (nullptr != m_spxmlDoc.get()) return false;

    if ( !MGValidate().Init ( pszFilespec ) )
    {

        LOG << "ERROR: Configuration xmls validation failed!!!";
        return false; // TODO: uncomment when xmls are perfect
    }

    m_spxmlDoc.reset ( new pugi::xml_document() );

    pugi::xml_parse_result result = m_spxmlDoc->load_file ( pszFilespec, pugi::parse_default | pugi::parse_pi );

    if ( !result )
    {

        LOG << "XML Error description: " << result.description();
        LOG << "XML Error offset: " << result.offset << "]\n";

        return false;
    }
    SetSeriesType();

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

bool MGConfig::GetInteger ( const char* pszSection, const char* pszEntry, int& nValue ) const
{

    pugi::xml_node node;
    if ( GetEntryNode ( m_spxmlDoc.get(), pszSection, pszEntry, node ) )
    {

        nValue = node.attribute ( g_strXmlAttrValue.c_str() ).as_int();
        return true;
    }

    return false;
}

bool MGConfig::GetFloat(const char* pszSection, const char* pszEntry, float& nValue) const {

    pugi::xml_node node;
    if (GetEntryNode(m_spxmlDoc.get(), pszSection, pszEntry, node)) {

        nValue = node.attribute(g_strXmlAttrValue.c_str()).as_float();
        return true;
    }

    return false;
}


bool MGConfig::GetBool(const char* pszSection, const char* pszEntry, bool& nValue) const {

    pugi::xml_node node;
    if (GetEntryNode(m_spxmlDoc.get(), pszSection, pszEntry, node)) {

        nValue = node.attribute(g_strXmlAttrValue.c_str()).as_bool();
        return true;
    }

    return false;
}

bool MGConfig::GetString ( const char* pszSection, const char* pszEntry, std::string& strValue ) const
{

    pugi::xml_node node;
    if ( GetEntryNode ( m_spxmlDoc.get(), pszSection, pszEntry, node ) )
    {

        strValue = node.attribute ( g_strXmlAttrValue.c_str() ).as_string();
        return true;
    }

    return false;
}



bool MGConfig::GetGames ( std::vector<GameDesc>& vecGames ) const
{

    if ( nullptr == m_spxmlDoc.get() )
    {
        return false;
    }

    vecGames.clear();

    pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ( "//*" ); // traverse all nodes, TODO: use xpath
    for ( pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it )
    {

        pugi::xml_node node = it->node();

        if ( g_strXmlNodeGame != node.name() )
        {
            continue;
        }

        GameDesc game;
        game.m_uGameId = node.attribute ( g_strXmlAttrId.c_str() ).as_int();
        game.m_uPosition = node.attribute ( g_strXmlAttrPosition.c_str() ).as_int();

        std::string strDirName = node.attribute ( g_strXmlAttrTargetName.c_str() ).as_string();
        if(strDirName.empty())
        {
            // The 'target_name' attribute is missing(probably only one instance of the library is required),
            //  so use the dir name as target name
            strDirName = node.attribute ( g_strXmlAttrDir.c_str() ).as_string();
        }
        std::stringstream ss;

         // Games shared objects are constructed the following way:
         // lib + ps_game_name + .so
        ss << "./lib" << strDirName << ".so";
        game.m_strLibso = ss.str();
        ss.str("");

        // Games service functions shared objects are constructed the following way:
        // libSf + ps_game_name + .so
        ss << "./libSf" << strDirName << ".so";
        game.m_strSfLibso = ss.str();

        game.m_strName = node.attribute ( g_strXmlAttrName.c_str() ).as_string();
        game.m_strType = node.attribute ( g_strXmlAttrType.c_str() ).as_string();
        game.m_strSubType = node.attribute ( g_strXmlAttrSubType.c_str() ).as_string();

        if ( 0 != game.m_uGameId && !strDirName.empty() )
        {
            vecGames.push_back ( game );
        }
    }

    return !vecGames.empty();
}

bool MGConfig::GetSecondScreenResourcesValues (std::vector<SecondScreenResourcesData> &vSecondScrData)
{

    pugi::xml_document doc ;

    if (nullptr == m_spxmlDoc.get())
    {
        return false;
    }

    {

        pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ("//resources_scr_2/*"); // traverse all nodes, TODO: use xpath

        pugi::xpath_node_set::const_iterator it = xset.begin();
        pugi::xml_node node = it->node().first_child();


        std::string path = node.value();
        path.erase(std::remove(path.begin(), path.end(), ' '), path.end());

        std::string series, product, name;
        GetProduct(series, product, name);
        std::stringstream ss;
        /* build the full path to the xml*/
        ss << "../series_" << series.c_str() << "/product_" << product.c_str() <<"/" << path.c_str();

        pugi::xml_parse_result result = doc.load_file(path.c_str(), pugi::parse_default | pugi::parse_pi); // for <?include?>

        if (!result) {

            eCDebug( LOG_CATEGORY_STORAGE ) << "Failed to load " <<  path << ": " <<  result.description() << " : error at " <<  result.offset;
            return false;
        }

    }

    pugi::xpath_node_set xset = doc.select_nodes ("//second_screen_data/*");
    for ( pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it )
    {

        SecondScreenResourcesData SecondScr_Values;

        pugi::xml_node node = it->node();

        SecondScr_Values.name = node.attribute("name").as_string();
        SecondScr_Values.value = node.attribute("value").as_string();

        vSecondScrData.push_back(SecondScr_Values);
    }


    return true;
}


bool MGConfig::GetPowerGameVariantsValues(std::vector<SeriesPowerGameVariantsData> &vPowerGamesData)
{

    pugi::xml_document doc ;

    if (nullptr == m_spxmlDoc.get())
    {
                return false;
    }

    {

        pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ("//power_variants/*"); // traverse all nodes, TODO: use xpath

        pugi::xpath_node_set::const_iterator it = xset.begin();
        pugi::xml_node node = it->node().first_child();


        std::string path = node.value();
        path.erase(std::remove(path.begin(), path.end(), ' '), path.end());

        std::string series, product, name;
        GetProduct(series, product, name);
        std::stringstream ss;
        /* build the full path to the xml*/
        ss << "../series_" << series.c_str() << "/product_" << product.c_str() <<"/" << path.c_str();

        pugi::xml_parse_result result = doc.load_file(path.c_str(), pugi::parse_default | pugi::parse_pi); // for <?include?>

        if (!result) {

            eCDebug( LOG_CATEGORY_STORAGE ) << "Failed to load " <<  path << ": " <<  result.description() << " : error at " <<  result.offset;
            return false;
        }

    }

    pugi::xpath_node_set xset = doc.select_nodes ("//power_custom_variants/*");
    for ( pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it )
    {

        SeriesPowerGameVariantsData PowerGameVariants_Values;

        pugi::xml_node node = it->node();

        PowerGameVariants_Values.GameID = node.attribute("GameID").as_int();
        PowerGameVariants_Values.GameVariantInex = node.attribute("value").as_int();

        vPowerGamesData.push_back(PowerGameVariants_Values);
    }


    return true;
}

bool MGConfig::GetProduct ( std::string& series, std::string& product, std::string& name ) const
{

    if ( nullptr == m_spxmlDoc.get() )
    {
        return false;
    }

    pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ( "//*" );
    for ( pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it )
    {

        pugi::xml_node node = it->node();

        if ( g_strXmlNodeVersion != node.name() )
        {
            continue;
        }

        series = node.attribute ( g_strXmlAttrSeries.c_str() ).as_string();
        product = node.attribute ( g_strXmlAttrProduct.c_str() ).as_string();
        name = node.attribute ( g_strXmlAttrName.c_str() ).as_string();
        return true;
    }

    return false;
}

void MGConfig::SetSeriesType ()
{
    std::string series;
    std::string product;
    pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ( "//*" );

    for ( pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it )
    {
        pugi::xml_node node = it->node();

        if ( g_strXmlNodeVersion != node.name() )
        {
            continue;
        }
        series = node.attribute ( g_strXmlAttrSeries.c_str() ).as_string();
        product = node.attribute ( g_strXmlAttrProduct.c_str() ).as_string();

        break;
    }

    if(strcasecmp(series.c_str(),"Test") == 0){
        m_SeriesType =  eTest;
    }else if(strcasecmp(series.c_str(),"Collection") == 0){
        m_SeriesType =  eCollection;
    }else if(strcasecmp(series.c_str(),"Power") == 0){
        m_SeriesType =  ePower;
    }else if(strcasecmp(series.c_str(),"Premier") == 0){
        m_SeriesType =  ePremier;
    }else if(strcasecmp(series.c_str(),"Color") == 0){
        m_SeriesType =  eColor;
    }else if(strcasecmp(series.c_str(),"4HappyHits") == 0){
        m_SeriesType =  e4HappyHits;
    }else if(strcasecmp(series.c_str(),"DiamondLife") == 0){
        m_SeriesType =  eDiamondLife;
    }else if(strcasecmp(series.c_str(),"China") == 0){
        m_SeriesType =  eChina;
    }else if( strcasecmp( series.c_str() , "UnitedDreams" ) == 0 ){
        m_SeriesType = eUnitedDreams;
    }else if(strcasecmp(series.c_str(),"GrandStrike") == 0){
        m_SeriesType =  eGrandStrike;
    }else if( strcasecmp( series.c_str() , "Union" ) == 0 ){
        m_SeriesType = eUnion;
    }
    else if( strcasecmp( series.c_str() , "AWP" ) == 0 ){
        m_SeriesType = eAWP;
    }
    else{
        /** I hope we do not get to 100 multigames. */
        m_SeriesType =  100;
    }

    /** Need to set the product version here*/
    SetProductVersion(product);

}

const char* MGConfig::GetSeriesName(ESeriesVariants sType) const
{
    switch (sType)
    {
    case eTest:         return "Test";
    case eCollection:   return "Collection";
    case ePower:        return "Power";
    case ePremier:      return "Premier";
    case eColor:        return "Color";
    case e4HappyHits:   return "4HappyHits";
    case eDiamondLife:   return "DiamondLife";
    case eChina:        return "China";
    case eUnitedDreams:  return static_cast<const char*>("UnitedDreams");
    case eGrandStrike:	return "GrandStrike";
    case eUnion:  return "Union";
    case eAWP:  return "AWP";
    default:
        break;
    }
    return "UNKNOWN";
}

const char* MGConfig::GetSeriesName() const
{
    return GetSeriesName(static_cast<ESeriesVariants>(GetSeriesType()));
}

void MGConfig::SetProductVersion(std::string ProductNumber)
{
  switch(m_SeriesType){
  case eCollection:{
    if( strcasecmp(ProductNumber.c_str(),"orange") == 0 ){
      m_ProductVersion = 1;
    }
    else if(strcasecmp(ProductNumber.c_str(),"orangeRO") == 0 ){
      m_ProductVersion = 1;
    }
    else if(strcasecmp(ProductNumber.c_str(),"all") == 0){
      m_ProductVersion = 1;
    }
    else if(strcasecmp(ProductNumber.c_str(),"red") == 0 ){
      m_ProductVersion = 2;
    }
    else if( strcasecmp(ProductNumber.c_str(),"green" ) == 0 ){
      m_ProductVersion = 3;
    }
    else if( strcasecmp(ProductNumber.c_str(),"greenRO" ) == 0 ){
      m_ProductVersion = 3;
    }
    else if(strcasecmp(ProductNumber.c_str(),"purple") == 0){
      m_ProductVersion = 4;
    }
    else if(strcasecmp(ProductNumber.c_str(),"fruits") == 0){
      m_ProductVersion = 5;
    }
    else if(strcasecmp(ProductNumber.c_str(),"fruits2") == 0){
      m_ProductVersion = 6;
    }
    else if(strcasecmp(ProductNumber.c_str(),"fruitsRO") == 0){
      m_ProductVersion = 7;
    }
    else if( strcasecmp(ProductNumber.c_str(),"union") == 0 ){
      m_ProductVersion = 8;
    }
    else{
      /* Wrong product number in multigame.xml for this multigame */
      m_ProductVersion = 0;
    }
    break;
  }
    case eUnitedDreams:
    {
        if( strcasecmp(ProductNumber.c_str(),"orange") == 0 )
        {
            m_ProductVersion = 1;
        }
        else if( strcasecmp(ProductNumber.c_str(),"green") == 0 )
        {
            m_ProductVersion = 2;
        }
        else
        {
            /* Wrong product number in multigame.xml for this multigame */
            m_ProductVersion = 0;
        }
        break;
    }

    case ePower:{
        if(strcasecmp(ProductNumber.c_str(),"one") == 0){
            m_ProductVersion = 1;
        }else if(strcasecmp(ProductNumber.c_str(),"two") == 0){
            m_ProductVersion = 2;
        }else if((strcasecmp(ProductNumber.c_str(),"red") == 0) ||
                 (strcasecmp(ProductNumber.c_str(),"red.rom.ver.1") == 0) ||
                 (strcasecmp(ProductNumber.c_str(),"red.srb.ver.1") == 0) ){
            m_ProductVersion = 3;
        }else if(strcasecmp(ProductNumber.c_str(),"green") == 0){
            m_ProductVersion = 4;
        }else if(strcasecmp(ProductNumber.c_str(),"purple") == 0){
            m_ProductVersion = 5;
        }else if(strcasecmp(ProductNumber.c_str(),"blue") == 0){
            m_ProductVersion = 6;
        }else{
            /* Wrong product number in multigame.xml for this multigame */
            m_ProductVersion = 0;
        }

        break;
    }
    case e4HappyHits:{
        if(strcasecmp(ProductNumber.c_str(),"one") == 0){
            m_ProductVersion = 1;
        }else if(strcasecmp(ProductNumber.c_str(),"two") == 0){
            m_ProductVersion = 2;
        }else{
            /* Wrong product number in multigame.xml for this multigame */
            m_ProductVersion = 0;
        }

        break;
    }
    case eChina:{
        if(strcasecmp(ProductNumber.c_str(),"one") == 0){
            m_ProductVersion = 1;
        }else{
            /* Wrong product number in multigame.xml for this multigame */
            m_ProductVersion = 0;
        }
        break;
    }
    case eGrandStrike:{
        if(strcasecmp(ProductNumber.c_str(),"one") == 0){
            m_ProductVersion = 1;
        }
        break;
    }
    case eDiamondLife:{
        if(strcasecmp(ProductNumber.c_str(),"one") == 0){
            m_ProductVersion = 1;
        }else{
            /* Wrong product number in multigame.xml for this multigame */
            m_ProductVersion = 0;
        }
        break;
    }
    case eUnion:
        if(strcasecmp(ProductNumber.c_str(),"one") == 0){
            m_ProductVersion = 1;
        }else{
            /* Wrong product number in multigame.xml for this multigame */
            m_ProductVersion = 0;
        }
        break;
    case eAWP:
        if(strcasecmp(ProductNumber.c_str(),"spain") == 0){
            m_ProductVersion = 1;
        }else if(strcasecmp(ProductNumber.c_str(),"redUKB1") == 0){
            m_ProductVersion = 1;
        }
        else{
            /* Wrong product number in multigame.xml for this multigame */
            m_ProductVersion = 0;
        }
        break;

    default : {
        m_ProductVersion = 0;
    }
    }

}

int MGConfig::GetSeriesType() const
{
    return m_SeriesType;
}


int MGConfig::GetProductVersion()
{
    return m_ProductVersion;
}

bool MGConfig::GetDemoSequence ( std::vector<DemoEvent>& vecSequence ) const
{
    if ( nullptr == m_spxmlDoc.get() )
    {
        return false;
    }

    pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ( "//*" );
    for ( pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it )
    {

        pugi::xml_node node = it->node();

        if ( g_strXmlNodeEvent != node.name() )
        {
            continue;
        }

        DemoEvent t;
        t.mName = node.attribute ( g_strXmlAttrName.c_str() ).as_string();
        t.mValue = node.attribute ( g_strXmlAttrValue.c_str() ).as_int();
        vecSequence.push_back ( t );
    }

    return vecSequence.empty() == false;
}


bool MGConfig::GetJurisdictions ( std::map<unsigned, std::string>& mapJurisdictions ) const
{

    if ( nullptr == m_spxmlDoc.get() )
    {
        return false;
    }

    mapJurisdictions.clear();

    pugi::xpath_node_set xset = m_spxmlDoc->select_nodes ( "//*" ); // traverse all nodes, TODO: use xpath
    for ( pugi::xpath_node_set::const_iterator it = xset.begin(); it != xset.end(); ++it )
    {

        pugi::xml_node node = it->node();

        if ( g_strXmlNodeJurisdiction != node.name() )
        {
            continue;
        }

        unsigned uId = node.attribute ( g_strXmlAttrId.c_str() ).as_int();
        std::string strName = node.attribute ( g_strXmlAttrName.c_str() ).as_string();
        std::string strAllowed = node.attribute ( g_strXmlAttrAllowed.c_str() ).as_string();

#ifdef EGT_DEBUG
        strAllowed = g_strXmlAllowedYes; // all jurisdictions are allowed in debug
#endif //  EGT_DEBUG

        if ( !strName.empty() && ( g_strXmlAllowedYes == strAllowed ) )
        {

            mapJurisdictions[ uId ] = strName;
        }
    }

    return !mapJurisdictions.empty();
}

MGConfig gMGCfg;
