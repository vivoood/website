#include "Constants.h"

Constants::Constants()
{
    m_Header.strTemplateName = "web-site-name-template";
    m_Header.strBindName = "web-site-name";
    m_Header.strBindSlogan = "web-site-slogan";
    m_Header.strTitle = "Some Title";
    m_Header.strSlogan = "use some slogan";

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
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "About us";
    d.strTabButtonStyle = "menu-buttons";
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "FAQ's";
    d.strTabButtonStyle = "menu-buttons";
    m_Tabs.vTabButtons.push_back ( d );

    /** ******************************************* */

    std::vector<WidgetData::STableData> vTableRow;
    WidgetData::STableData dTable;

    dTable.strStyle = "table-col-1";
    dTable.strLenght = "15%";
    dTable.strWidgetName = "WContainerWidget";
    vTableRow.push_back ( dTable );

//     dTable.strBgrImg.assign("airplane_interior");
    dTable.strStyle = "table-col-2";
    dTable.strLenght = "65%";
    dTable.strWidgetName = "CWTabs";
    vTableRow.push_back ( dTable );

    dTable.strStyle = "table-col-3";
    dTable.strLenght = "25%";
    dTable.strWidgetName = "CWPublicOffers";
    vTableRow.push_back ( dTable );

    m_Table.vTable.push_back ( vTableRow );

    /** ******************************************* */

    WidgetData::SOffer o;

    o.bOneWay = true;
    o.bDirectFlight = true;
    o.strFrom = "Sofia";
    o.strTo = "Vienna";
    o.strPrice = "$ 36";
    o.strAirline = "Wizz Air";
    
    m_Offers.m_Offers.push_back ( o );

    o.bOneWay = false;
    o.bDirectFlight = true;
    o.strFrom = "Milano";
    o.strTo = "Paris";
    o.strPrice = "$ 87";
    o.strAirline = "Wizz Air";
    m_Offers.m_Offers.push_back ( o );

    o.bOneWay = false;
    o.bDirectFlight = false;
    o.strFrom = "Rome";
    o.strTo = "Brazil";
    o.strPrice = "$ 135";
    o.strAirline = "Asia air";
    m_Offers.m_Offers.push_back ( o );

    o.bOneWay = true;
    o.bDirectFlight = false;
    o.strFrom = "Istanbul";
    o.strTo = "China";
    o.strPrice = "$ 77";
    o.strAirline = "Asia air";
    m_Offers.m_Offers.push_back ( o );

    o.bOneWay = true;
    o.bDirectFlight = true;
    o.strFrom = "Bulgaria";
    o.strTo = "Germany";
    o.strPrice = "$ 42";
    o.strAirline = "Bulgaria air";
    m_Offers.m_Offers.push_back ( o );
    

    /** ******************************************* */

    m_Footer.strStyle = "footer-style";
}

Constants gConstants;
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

