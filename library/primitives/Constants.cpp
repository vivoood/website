#include "Constants.h"

Constants::Constants()
{
    strSiteName.assign ( "Some Title" );
    strSiteSlogan.assign ( "use some slogan" );

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

    std::vector<WidgetData::STableData> vTableRow;
    WidgetData::STableData dTable;

    dTable.strStyle = "table-col-1";
    dTable.strLenght = "15%";
    dTable.strWidgetName = "WContainerWidget";
    vTableRow.push_back ( dTable );

    dTable.strStyle = "table-col-2";
    dTable.strLenght = "65%";
    dTable.strWidgetName = "WTabs";
    vTableRow.push_back ( dTable );

    dTable.strStyle = "table-col-3";
    dTable.strLenght = "25%";
    dTable.strWidgetName = "WContainerWidget";
    vTableRow.push_back ( dTable );

    m_Table.vTable.push_back ( vTableRow );
}

Constants gConstants;
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

