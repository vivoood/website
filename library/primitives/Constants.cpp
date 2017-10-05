#include "Constants.h"

Constants::Constants()
{
    m_Header.strTemplateName = "web-site-name-template";
    m_Header.strBindName = "web-site-name";
    m_Header.strBindSlogan = "web-site-slogan";
    m_Header.strTitle = "Some Title";
    m_Header.strSlogan = "use some slogan";

    /** ******************************************* */
    /** ******************************************* */
    m_Tabs.strTabStyle = "menu-buttons-bgr";

    WidgetData::STabButtonsData d;

    d.strTabName = "Home";
    d.strTabButtonStyle = "menu-buttons";
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "News";
    d.strTabButtonStyle = "menu-buttons";
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "Travel tips";
    d.strTabButtonStyle = "menu-buttons";
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "Contacts";
    d.strTabButtonStyle = "menu-buttons";

    d.content.strChildWidget = "CWContacts";
    d.content.strWidgetStyle = "contacts-style";

    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "FAQ's";
    d.strTabButtonStyle = "menu-buttons";

    d.content.strChildWidget = "CWFAQ";
    d.content.strWidgetStyle = "faq-style";

    m_Tabs.vTabButtons.push_back ( d );

    /** ******************************************* */
    /** ******************************************* */

    m_TabsAfterLogin.strTabStyle = "menu-buttons-bgr";

    WidgetData::STabButtonsData dlogin;

    dlogin.strTabName = "Home";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.content.strChildWidget = "";
    dlogin.content.strWidgetStyle = "";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "Contacts";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.content.strChildWidget = "CWContacts";
    dlogin.content.strWidgetStyle = "contacts-style";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "FAQ's";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.content.strChildWidget = "CWFAQ";
    dlogin.content.strWidgetStyle = "faq-style";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "My account";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.content.strChildWidget = "";
    dlogin.content.strWidgetStyle = "";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    /** ******************************************* */
    /** ******************************************* */

    std::vector<WidgetData::STableData> vTableRow;
    WidgetData::STableData dTable;

    dTable.strStyle = "table-col-1";
    dTable.strLenght = "15%";
    dTable.strWidgetName = "CWLeftCol";
    dTable.strWidgetData = "SLeftCol";
    vTableRow.push_back ( dTable );

    dTable.strStyle = "table-col-2";
    dTable.strLenght = "65%";
    dTable.strWidgetName = "CWTabs";
    dTable.strWidgetData = "STabs";
    vTableRow.push_back ( dTable );

    dTable.strStyle = "table-col-3";
    dTable.strLenght = "25%";
    dTable.strWidgetName = "CWPublicOffers";
    dTable.strWidgetData = "SOffers";
    vTableRow.push_back ( dTable );

    m_Table.vTable.push_back ( vTableRow );

    /** ******************************************* */

    std::vector<WidgetData::STableData> vTableRowAfterLogin;
    WidgetData::STableData dTableAfterLogin;

    dTableAfterLogin.strStyle = "table-col-1";
    dTableAfterLogin.strLenght = "15%";
    dTableAfterLogin.strWidgetName = "CWLeftCol";
    dTableAfterLogin.strWidgetData = "SLeftColAfterLogin";
    vTableRowAfterLogin.push_back ( dTableAfterLogin );

    dTableAfterLogin.strStyle = "table-col-2";
    dTableAfterLogin.strLenght = "65%";
    dTableAfterLogin.strWidgetName = "CWTabs";
    dTableAfterLogin.strWidgetData = "STabsAfterLogin";
    vTableRowAfterLogin.push_back ( dTableAfterLogin );

    dTableAfterLogin.strStyle = "table-col-3";
    dTableAfterLogin.strLenght = "25%";
    dTableAfterLogin.strWidgetName = "CWPublicOffers";
    dTableAfterLogin.strWidgetData = "SOffers";
    vTableRowAfterLogin.push_back ( dTableAfterLogin );

    m_TableAfterLogin.vTable.push_back ( vTableRowAfterLogin );

    /** ******************************************* */
    /** ******************************************* */

    WidgetData::SOffer o;

    o.offerBig.bOneWay = true;
    o.offerBig.bDirectFlight = true;
    o.offerBig.strFrom = "Sofia";
    o.offerBig.strTo = "Vienna";
    o.offerBig.strPrice = "$ 36";
    o.offerBig.strAirline = "Wizz Air";
    o.offerBig.strHyperlink = "https://wizzair.com/";
    m_Offers.m_Offers.push_back ( o );

    o.offerBig.bOneWay = false;
    o.offerBig.bDirectFlight = true;
    o.offerBig.strFrom = "Milano";
    o.offerBig.strTo = "Paris";
    o.offerBig.strPrice = "$ 87";
    o.offerBig.strAirline = "Wizz Air";
    o.offerBig.strHyperlink = "https://wizzair.com/";
    m_Offers.m_Offers.push_back ( o );

    o.offerBig.bOneWay = false;
    o.offerBig.bDirectFlight = false;
    o.offerBig.strFrom = "Rome";
    o.offerBig.strTo = "Brazil";
    o.offerBig.strPrice = "$ 135";
    o.offerBig.strAirline = "Air asia";
    o.offerBig.strHyperlink = "https://www.airasia.com";
    m_Offers.m_Offers.push_back ( o );

    o.offerBig.bOneWay = true;
    o.offerBig.bDirectFlight = false;
    o.offerBig.strFrom = "Istanbul";
    o.offerBig.strTo = "China";
    o.offerBig.strPrice = "$ 77";
    o.offerBig.strAirline = "Air asia";
    o.offerBig.strHyperlink = "https://www.airasia.com";
    m_Offers.m_Offers.push_back ( o );

    o.offerBig.bOneWay = true;
    o.offerBig.bDirectFlight = true;
    o.offerBig.strFrom = "Bulgaria";
    o.offerBig.strTo = "Germany";
    o.offerBig.strPrice = "$ 42";
    o.offerBig.strAirline = "Bulgaria air";
    o.offerBig.strHyperlink = "https://www.air.bg";
    m_Offers.m_Offers.push_back ( o );

    /** ******************************************* */

    m_Login.strStyleBtns = "login-button-style";
    m_Login.strStyleFields = "login-fields-style";
    m_Login.strStyleCommon = "login-style";
    m_Login._register.strStyleButton = "menu-buttons";
    m_Login._register.strStyleError = "register-error";


    m_LeftCol.m_vWidgets.push_back ( std::pair<std::string, std::string> ( "CWLogin", "SLogin" ) );
    m_LeftColAfterLogin.m_vWidgets.push_back ( std::pair<std::string, std::string> ( "CWAfterLogin", "SLogin" ) );

    /** ******************************************* */

    m_UserLineInput.strStyleContainer = "user-line-input-container";
    m_UserLineInput.strStyleLabel = "user-line-input-label";
    m_UserLineInput.strStyleLineEdit = "user-line-input-button";

    m_UserComboInput.strStyleContainer = "user-combo-input-container";
    m_UserComboInput.strStyleLabel = "user-combo-input-label";
    m_UserComboInput.strStyleLineEdit = "user-combo-input-button";

    /** ******************************************* */

    m_Footer.strStyle = "footer-style";

    /** ******************************************* */

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SHeader", &m_Header ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STable", &m_Table ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STableAfterLogin", &m_TableAfterLogin ) )
    ;
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabs", &m_Tabs ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabsAfterLogin", &m_TabsAfterLogin ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SOffers", &m_Offers ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLeftCol", &m_LeftCol ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLeftColAfterLogin", &m_LeftColAfterLogin ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SFooter", &m_Footer ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLogin", &m_Login ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SUserLineInput", &m_UserLineInput ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SUserComboInput", &m_UserComboInput ) );

//     m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "", & ) );

}

IWidgetData * Constants::GetData ( std::string str, std::string strHash )
{
    std::map<std::string, IWidgetData*>::iterator it;
    it = m_mapData.find ( str );
    if ( it == m_mapData.end() )
        return nullptr;

    ( *it ).second->strHash = strHash;
    return ( *it ).second;
}

Constants gConstants;
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
