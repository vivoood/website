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

    dlogin.strTabName = "My account";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.content.strChildWidget = "";
    dlogin.content.strWidgetStyle = "";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "Queries";
    dlogin.strTabButtonStyle = "menu-buttons";
    dlogin.content.strChildWidget = "";
    dlogin.content.strWidgetStyle = "";
    m_TabsAfterLogin.vTabButtons.push_back ( dlogin );

    dlogin.strTabName = "Add query";
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
    dTableAfterLogin.strLenght = "70%";
    dTableAfterLogin.strWidgetName = "CWTabs";
    dTableAfterLogin.strWidgetData = "STabsAfterLogin";
    vTableRowAfterLogin.push_back ( dTableAfterLogin );

    dTableAfterLogin.strStyle = "table-col-3";
    dTableAfterLogin.strLenght = "15%";
    dTableAfterLogin.strWidgetName = "CWPublicOffers";
    dTableAfterLogin.strWidgetData = "SOffers";
    vTableRowAfterLogin.push_back ( dTableAfterLogin );

    m_TableAfterLogin.vTable.push_back ( vTableRowAfterLogin );

    /** ******************************************* */

    std::vector<WidgetData::STableData> vTableRowOwnerLogin;
    WidgetData::STableData dTableOwnerLogin;

    dTableOwnerLogin.strStyle = "table-col-1";
    dTableOwnerLogin.strLenght = "10%";
    dTableOwnerLogin.strWidgetName = "CWLeftCol";
    dTableOwnerLogin.strWidgetData = "SLeftColAfterLogin";
    vTableRowOwnerLogin.push_back ( dTableOwnerLogin );

    dTableOwnerLogin.strStyle = "table-col-2";
    dTableOwnerLogin.strLenght = "30%";
    dTableOwnerLogin.strWidgetName = "WContainerWidget";
    dTableOwnerLogin.strWidgetData = "";
    vTableRowOwnerLogin.push_back ( dTableOwnerLogin );

    dTableOwnerLogin.strStyle = "table-col-3";
    dTableOwnerLogin.strLenght = "30%";
    dTableOwnerLogin.strWidgetName = "WContainerWidget";
    dTableOwnerLogin.strWidgetData = "";
    vTableRowOwnerLogin.push_back ( dTableOwnerLogin );

    dTableOwnerLogin.strStyle = "table-col-4";
    dTableOwnerLogin.strLenght = "30%";
    dTableOwnerLogin.strWidgetName = "WContainerWidget";
    dTableOwnerLogin.strWidgetData = "";
    vTableRowOwnerLogin.push_back ( dTableOwnerLogin );

    m_TableOwnerLogin.vTable.push_back ( vTableRowOwnerLogin );

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

    m_ContiCtryInput.strStyleContainer = "contictry";
    m_ContiCtryInput.strStyleLabel = "";
    m_ContiCtryInput.strStyleLineEdit = "";

    /** ******************************************* */

    m_MyAccount.strStyle = "my-account";

    m_radioButtons.strStyle = "paybonam";
    m_radioButtons.strMainMsg = "Choose payment abonament";
    m_radioButtons.content.push_back ( std::make_pair<std::string, std::string> ( "2.99$", "cheap variant - description ?!?!?!" ) );
    m_radioButtons.content.push_back ( std::make_pair<std::string, std::string> ( "4.99$", "middle variant - description ?!?!?!" ) );
    m_radioButtons.content.push_back ( std::make_pair<std::string, std::string> ( "5.99$", "expensive variant - description ?!?!?!" ) );

    /** ******************************************* */

    m_Footer.strStyle = "footer-style";

    /** ******************************************* */

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SHeader", &m_Header ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STable", &m_Table ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STableAfterLogin", &m_TableAfterLogin ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STableOwnerLogin", &m_TableOwnerLogin ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabs", &m_Tabs ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "STabsAfterLogin", &m_TabsAfterLogin ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SOffers", &m_Offers ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLeftCol", &m_LeftCol ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLeftColAfterLogin", &m_LeftColAfterLogin ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SMyAccount", &m_MyAccount ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SRadioButtons", &m_radioButtons ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SFooter", &m_Footer ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SLogin", &m_Login ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SUserLineInput", &m_UserLineInput ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SUserComboInput", &m_UserComboInput ) );
    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SContiCtryInput", &m_ContiCtryInput ) );

    m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "SContiCtry", &m_ContiCtry ) );

//     m_mapData.insert ( std::pair<std::string, IWidgetData*> ( "", & ) );


    /** ******************************************* */
    /** ******************************************* */
    /** ******************************************* */

    m_ContiCtry.strStyle = "contictry";
    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > > ( "Africa",
    {
        "Algeria",
        "Angola",
        "Benin",
        "Botswana",
        "Burkina",
        "Burundi",
        "Cameroon",
        "Cape Verde",
        "Central African Republic",
        "Chad",
        "Comoros",
        "Congo",
        "Congo, Democratic ",
        "Djibouti",
        "Egypt",
        "Equatorial Guinea",
        "Eritrea",
        "Ethiopia",
        "Gabon",
        "Gambia",
        "Ghana",
        "Guinea",
        "Guinea-Bissau",
        "Ivory Coast",
        "Kenya",
        "Lesotho",
        "Liberia",
        "Libya",
        "Madagascar",
        "Malawi",
        "Mali",
        "Mauritania",
        "Mauritius",
        "Morocco",
        "Mozambique",
        "Namibia",
        "Niger",
        "Nigeria",
        "Rwanda",
        "Sao Tome and Principe",
        "Senegal",
        "Seychelles",
        "Sierra Leone",
        "Somalia",
        "South Africa",
        "South Sudan",
        "Sudan",
        "Swaziland",
        "Tanzania",
        "Togo",
        "Tunisia",
        "Uganda",
        "Zambia",
        "Zimbabwe"
    } ) );

    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > > ( "Asia",
    {
        "Afghanistan",
        "Bahrain",
        "Bangladesh",
        "Bhutan",
        "Brunei",
        "Burma ( Myanmar )",
        "Cambodia",
        "China",
        "East Timor",
        "India",
        "Indonesia",
        "Iran",
        "Iraq",
        "Israel",
        "Japan",
        "Jordan",
        "Kazakhstan",
        "Korea, North",
        "Korea, South",
        "Kuwait",
        "Kyrgyzstan",
        "Laos",
        "Lebanon",
        "Malaysia",
        "Maldives",
        "Mongolia",
        "Nepal",
        "Oman",
        "Pakistan",
        "Philippines",
        "Qatar",
        "Russian Federation",
        "Saudi Arabia",
        "Singapore",
        "Sri Lanka",
        "Syria",
        "Tajikistan",
        "Thailand",
        "Turkey",
        "Turkmenistan",
        "United Arab Emirates",
        "Uzbekistan",
        "Vietnam",
        "Yemen"
    } ) );

    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > > ( "Europe",
    {
        "Albania",
        "Andorra",
        "Armenia",
        "Austria",
        "Azerbaijan",
        "Belarus",
        "Belgium",
        "Bosnia and Herzegovina",
        "Bulgaria",
        "Croatia",
        "Cyprus",
        "Czech Republic",
        "Denmark",
        "Estonia",
        "Finland",
        "France",
        "Georgia",
        "Germany",
        "Greece",
        "Hungary",
        "Iceland",
        "Ireland",
        "Italy",
        "Latvia",
        "Liechtenstein",
        "Lithuania",
        "Luxembourg",
        "Macedonia",
        "Malta",
        "Moldova",
        "Monaco",
        "Montenegro",
        "Netherlands",
        "Norway",
        "Poland",
        "Portugal",
        "Romania",
        "San Marino",
        "Serbia",
        "Slovakia",
        "Slovenia",
        "Spain",
        "Sweden",
        "Switzerland",
        "Ukraine",
        "United Kingdom",
        "Vatican City"
    } ) );

    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > > ( "North America",
    {
        "Antigua and Barbuda",
        "Bahamas",
        "Barbados",
        "Belize",
        "Canada",
        "Costa Rica",
        "Cuba",
        "Dominica",
        "Dominican Republic",
        "El Salvador",
        "Grenada",
        "Guatemala",
        "Haiti",
        "Honduras",
        "Jamaica",
        "Mexico",
        "Nicaragua",
        "Panama",
        "Saint Kitts and Nevis",
        "Saint Lucia",
//         "Saint Vincent and the Grenadines",
        "Trinidad and Tobago",
        "United States"
    } ) );

    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > > ( "Oceania",
    {
        "Australia",
        "Fiji",
        "Kiribati",
        "Marshall Islands",
        "Micronesia",
        "Nauru",
        "New Zealand",
        "Palau",
        "Papua New Guinea",
        "Samoa",
        "Solomon Islands",
        "Tonga",
        "Tuvalu",
        "Vanuatu"
    } ) );

    m_ContiCtry._list.insert ( std::pair< std::string, std::vector< std::string > > ( "South America",
    {
        "Argentina",
        "Bolivia",
        "Brazil",
        "Chile",
        "Colombia",
        "Ecuador",
        "Guyana",
        "Paraguay",
        "Peru",
        "Suriname",
        "Uruguay",
        "Venezuela"
    } ) );
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
