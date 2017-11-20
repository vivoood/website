#include "Constants.h"

#include <algorithm>

#include "CWHash.h"
#include "CWOwnerData.h"
#include "ConstantsData.h"

Constants::Constants()
{
    /** ******************************************* */
    /** ******************************************* */
    m_Tabs.strTabStyle = "menu-buttons-bgr";

    WidgetData::STabButtonsData d;

    d.strTabName = "Home";
    d.strTabButtonStyle = "menu-buttons";
    d.strChildWidget = "n/a";
    d.strChildWidgetData = "empty";
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "How it works";
    d.strTabButtonStyle = "menu-buttons";
    d.strChildWidget = "n/a";
    d.strChildWidgetData = "empty";
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "Travel tips";
    d.strTabButtonStyle = "menu-buttons";
    d.strChildWidget = "n/a";
    d.strChildWidgetData = "empty";
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "Contacts";
    d.strTabButtonStyle = "menu-buttons";
    d.strChildWidget = "CWContacts";
    d.strChildWidgetData = "SContacts";
    m_Tabs.vTabButtons.push_back ( d );

    d.strTabName = "FAQ's";
    d.strTabButtonStyle = "menu-buttons";
    d.strChildWidget = "CWFAQ";
    d.strChildWidgetData = "SFaq";
    m_Tabs.vTabButtons.push_back ( d );

    /** ******************************************* */
    /** ******************************************* */

    m_TabsAfterLogin.strTabStyle = "menu-buttons-bgr";

    WidgetData::STabButtonsData dlogin;

    dlogin.strTabName = "Home";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.strChildWidget = "n/a";
    dlogin.strChildWidgetData = "empty";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "How it works";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.strChildWidget = "n/a";
    dlogin.strChildWidgetData = "empty";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "Add query";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.strChildWidget = "CWQuery";
    dlogin.strChildWidgetData = "SQuery";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "My queries";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.strChildWidget = "CWMyQueries";
    dlogin.strChildWidgetData = "SMyQuery";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "My history";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.strChildWidget = "n/a";
    dlogin.strChildWidgetData = "empty";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "Contacts";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.strChildWidget = "CWContacts";
    dlogin.strChildWidgetData = "SContacts";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "Client report";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.strChildWidget = "n/a";
    dlogin.strChildWidgetData = "n/a";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "FAQ's";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.strChildWidget = "CWFAQ";
    dlogin.strChildWidgetData = "SFaq";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    /** ******************************************* */
    /** ******************************************* */
    m_TabsOwner.strTabStyle = "menu-buttons-bgr";

    WidgetData::STabButtonsData downer;

    downer.strTabName = "Settings";
    downer.strTabButtonStyle = "menu-buttons";
    downer.strChildWidget = "CWOwnerSettings";
    downer.strChildWidgetData = "empty";
    m_TabsOwner.vTabButtons.push_back ( downer );

    downer.strTabName = "Add free offers";
    downer.strTabButtonStyle = "menu-buttons";
    downer.strChildWidget = "CWOwnerFreeOffers";
    downer.strChildWidgetData = "SOwnerFreeOffers";
    m_TabsOwner.vTabButtons.push_back ( downer );

    downer.strTabName = "View free offers";
    downer.strTabButtonStyle = "menu-buttons";
    downer.strChildWidget = "CWOwnerFreeOffersView";
    downer.strChildWidgetData = "SOwnerFreeOffers";
    m_TabsOwner.vTabButtons.push_back ( downer );


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
    dTable.strLenght = "70%";
    dTable.strWidgetName = "CWTabs";
    dTable.strWidgetData = "STabs";
    vTableRow.push_back ( dTable );

    dTable.strStyle = "table-col-3";
    dTable.strLenght = "15%";
    dTable.strWidgetName = "CWPublicOffers";
    dTable.strWidgetData = "SOffersRight";
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
    dTableAfterLogin.strLenght = "70%";
    dTableAfterLogin.strWidgetName = "CWTabs";
    dTableAfterLogin.strWidgetData = "STabsAfterLogin";
    vTableRowAfterLogin.push_back ( dTableAfterLogin );

    dTableAfterLogin.strStyle = "table-col-3";
    dTableAfterLogin.strLenght = "15%";
    dTableAfterLogin.strWidgetName = "CWPublicOffers";
    dTableAfterLogin.strWidgetData = "SOffersRight";
    vTableRowAfterLogin.push_back ( dTableAfterLogin );

    m_TableAfterLogin.vTable.push_back ( vTableRowAfterLogin );

    /** ******************************************* */

    std::vector<WidgetData::STableData> vTableRowOwnerLogin;
    WidgetData::STableData dTableOwnerLogin;

    dTableOwnerLogin.strStyle = "table-col-1";
    dTableOwnerLogin.strLenght = "15%";
    dTableOwnerLogin.strWidgetName = "CWLeftCol";
    dTableOwnerLogin.strWidgetData = "SLeftColAfterLogin";
    vTableRowOwnerLogin.push_back ( dTableOwnerLogin );

    dTableOwnerLogin.strStyle = "table-col-2";
    dTableOwnerLogin.strLenght = "70%";
    dTableOwnerLogin.strWidgetName = "CWTabs";
    dTableOwnerLogin.strWidgetData = "STabsOwner";
    vTableRowOwnerLogin.push_back ( dTableOwnerLogin );

    dTableOwnerLogin.strStyle = "table-col-3";
    dTableOwnerLogin.strLenght = "15%";
    dTableOwnerLogin.strWidgetName = "CWPublicOffers";
    dTableOwnerLogin.strWidgetData = "SOffersRight";
    vTableRowOwnerLogin.push_back ( dTableOwnerLogin );

    m_TableOwnerLogin.vTable.push_back ( vTableRowOwnerLogin );

    /** ******************************************* */
    /** ******************************************* */

    CWOwnerData owner;
    owner.LoadFreeOffers();

    std::vector<std::string> vOffers;
    for ( auto & i : owner.mapFreeOffers )
    {
        vOffers.push_back ( i.first );
    }

    if ( vOffers.size() < ( WidgetData::SOffersLeftRightBase::cnLeftSize + WidgetData::SOffersLeftRightBase::cnRightSize ) )
    {
        for ( unsigned int i = 0; i < vOffers.size(); i++ )
        {
            ( i % 2 == 0 ) ? m_OffersRight.m_OffersHashList.push_back ( vOffers[i] ) : m_OffersLeft.m_OffersHashList.push_back ( vOffers[i] );
        }
    }
    else
    {
        std::random_shuffle ( vOffers.begin(), vOffers.end() );
        for ( unsigned int i = 0; i < WidgetData::SOffersLeftRightBase::cnLeftSize; i++ )
        {
            m_OffersLeft.m_OffersHashList.push_back ( vOffers[i] );
        }

        for ( unsigned int i = 0; i < WidgetData::SOffersLeftRightBase::cnRightSize; i++ )
        {
            m_OffersRight.m_OffersHashList.push_back ( vOffers[i] );
        }
    }

    /** ******************************************* */

    m_Login.strStyleBtns = "login-button-style";
    m_Login.strStyleFields = "login-fields-style";
    m_Login.strStyleCommon = "login-style";
    m_Login._register.strStyleButton = "menu-buttons";
    m_Login._register.strStyleError = "register-error";


    m_LeftCol.m_vWidgets.push_back ( std::pair<std::string, std::string> ( "CWLogin", "SLogin" ) );
    m_LeftCol.m_vWidgets.push_back ( std::pair<std::string, std::string> ( "CWPublicOffers", "SOffersLeft" ) );

    m_LeftColAfterLogin.m_vWidgets.push_back ( std::pair<std::string, std::string> ( "CWAfterLogin", "SLogin" ) );
    m_LeftColAfterLogin.m_vWidgets.push_back ( std::pair<std::string, std::string> ( "CWPublicOffers", "SOffersLeft" ) );

    /** ******************************************* */

    m_UserLineInput.strStyleContainer = "user-line-input-container";
    m_UserLineInput.strStyleLabel = "user-line-input-label";
    m_UserLineInput.strStyleLineEdit = "user-line-input-button";

    m_UserComboInput.strStyleContainer = "user-combo-input-container";
    m_UserComboInput.strStyleLabel = "user-combo-input-label";
    m_UserComboInput.strStyleLineEdit = "user-combo-input-button";

    m_ContiCtryInput.strStyleContainer = "contictry";
    m_ContiCtryInput.strStyleLabel = "n/a";
    m_ContiCtryInput.strStyleLineEdit = "n/a";

    /** ******************************************* */

    m_MyAccount.strStyle = "my-account";

    m_radioButtons.strStyle = "paybonam";
    m_radioButtons.strMainMsg = "Choose payment abonament";
    m_radioButtons.content.push_back ( std::make_pair<std::string, std::string> ( "2.99$", "cheap variant - description ........... ?!?!?!" ) );
    m_radioButtons.content.push_back ( std::make_pair<std::string, std::string> ( "4.99$", "middle variant - description ........... ?!?!?!" ) );
    m_radioButtons.content.push_back ( std::make_pair<std::string, std::string> ( "9.99$", "expensive variant - description ........... ?!?!?!" ) );

    /** ******************************************* */

    m_Footer.strStyle = "footer-style";

    /** ******************************************* */

    m_OwnerFreeOffers.v = { {OwnerEID::from, "From", "WLineEdit", "style-free-offer-owner"}, {OwnerEID::to, "To", "WLineEdit", "style-free-offer-owner"}, {OwnerEID::price, "Price", "WLineEdit", "style-free-offer-owner"}, {OwnerEID::instead, "Instead", "WLineEdit", "style-free-offer-owner"}, {OwnerEID::airl, "Airline", "WLineEdit", "style-free-offer-owner"}, {OwnerEID::oneway, "One way ticket", "WCheckBox", ""}, {OwnerEID::direct, "Direct flight", "WCheckBox", ""}, {OwnerEID::link, "Link", "WLineEdit", "style-free-offer-owner"} };

    /** ******************************************* */


    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SHeader", &m_Header ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STable", &m_Table ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STableAfterLogin", &m_TableAfterLogin ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STableOwnerLogin", &m_TableOwnerLogin ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabs", &m_Tabs ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabsAfterLogin", &m_TabsAfterLogin ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabsOwner", &m_TabsOwner ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SOffer", &m_Offer ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SOffersLeft", &m_OffersLeft ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SOffersRight", &m_OffersRight ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLeftCol", &m_LeftCol ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLeftColAfterLogin", &m_LeftColAfterLogin ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SMyAccount", &m_MyAccount ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SRegister", &m_Login._register ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SRadioButtons", &m_radioButtons ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SContiCtry", &m_ContiCtry ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SFooter", &m_Footer ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLogin", &m_Login ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SUserLineInput", &m_UserLineInput ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SUserComboInput", &m_UserComboInput ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SContiCtryInput", &m_ContiCtryInput ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SQuery", &m_Query ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SMyQuery", &m_MyQuery ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SContacts", &m_Contacts ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SFaq", &m_Faq ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SOwnerFreeOffers", &m_OwnerFreeOffers ) );


    /** ******************************************* */
    /** ******************************************* */
    /** ******************************************* */

    m_ContiCtry.strStyle = "contictry";
    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > & > ( "Africa", ConstantsData::africa ) );
    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > & > ( "Asia", ConstantsData::asia ) );
    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > & > ( "Europe", ConstantsData::europe ) );
    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > & > ( "North America", ConstantsData::north_America ) );
    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > & > ( "Oceania", ConstantsData::oceania ) );
    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > & > ( "South America", ConstantsData::south_america ) );
}

#include "Debug.h"

IWidgetData * Constants::GetData ( std::string str, std::string strHash )
{
    std::map<std::string, IWidgetData*>::iterator it;
    it = m_mapData.find ( str );
    if ( it != m_mapData.end() )
    {
        ( *it ).second->strHash = strHash;
        return ( *it ).second;
    }

    if ( str == "empty" )
        return nullptr;

    Debug::print_backtrace ( strHash );
    return nullptr;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

