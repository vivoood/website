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

    m_TabsLogin.strTabStyle = "menu-buttons-bgr";

    WidgetData::STabButtonsData dlogin;

    dlogin.strTabName = "Home";
    dlogin.strTabButtonStyle = "menu-buttons";
    m_TabsLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "Contacts";
    dlogin.strTabButtonStyle = "menu-buttons";

    dlogin.content.strChildWidget = "CWContacts";
    dlogin.content.strWidgetStyle = "contacts-style";

    m_TabsLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "FAQ's";
    dlogin.strTabButtonStyle = "menu-buttons";

    dlogin.content.strChildWidget = "CWFAQ";
    dlogin.content.strWidgetStyle = "faq-style";

    m_TabsLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "My account";
    dlogin.strTabButtonStyle = "menu-buttons";
    m_TabsLogin.vTabButtons.push_back ( dlogin );

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

    m_LeftCol.login.strStyleBtns = "login-button-style";
    m_LeftCol.login.strStyleFields = "login-fields-style";
    m_LeftCol.login.strStyleCommon = "login-style";
    m_LeftCol.mapWidgets.insert ( std::pair<std::string, IWidgetData *> ( "CWLogin", &m_LeftCol.login ) );

    /** ******************************************* */

    m_Footer.strStyle = "footer-style";

    /** ******************************************* */

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SHeader", &m_Header ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STable", &m_Table ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabs", &m_Tabs ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabsLogin", &m_TabsLogin ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SOffers", &m_Offers ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLeftCol", &m_LeftCol ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SFooter", &m_Footer ) );

//     m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "", & ) );

}

IWidgetData * Constants::GetData ( std::string str )
{
    std::map<std::string, IWidgetData*>::iterator it;
    it = m_mapData.find ( str );
    if ( it == m_mapData.end() )
        return nullptr;
    return ( *it ).second;
}

Constants gConstants;
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
