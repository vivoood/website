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

    dTable.strStyle = "table-col-2";
    dTable.strLenght = "65%";
    dTable.strWidgetName = "CWTabs";
    vTableRow.push_back ( dTable );

    dTable.strStyle = "table-col-3";
    dTable.strLenght = "25%";
    dTable.strWidgetName = "CWOffer";
    vTableRow.push_back ( dTable );

    m_Table.vTable.push_back ( vTableRow );

    /** ******************************************* */

    m_Offer.bOneWay = true;
    m_Offer.bDirectFlight = true;
    
    m_Offer.strDirection = "<span> Sofia-Viena</span>";
    m_Offer.strPrice = "<span> 36$</span>";
    m_Offer.strAirline = "<span> Wizz Air</span>";
    
    m_Offer.strStyle = "offer-style";
    m_Offer.strPicAndStyle = std::pair<std::string, std::string> ( "pics/vienna.jpg" ,"offer-pic-style" );

    /** ******************************************* */

    m_Footer.strStyle = "footer-style";
}

Constants gConstants;
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

