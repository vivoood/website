#include "Constants.h"

Constants::Constants()
{
    strSiteName.assign ( "Create real site name" );
    strSiteSlogan.assign ( "use some slogan" );

    vTabs.push_back ( std::make_pair<std::string, std::string> ( "Home", "web-site-home" ) );
    vTabs.push_back ( std::make_pair<std::string, std::string> ( "News", "web-site-news" ) );
    vTabs.push_back ( std::make_pair<std::string, std::string> ( "Travel tips", "web-site-tips" ) );
    vTabs.push_back ( std::make_pair<std::string, std::string> ( "Contacts", "web-site-contacts" ) );
    vTabs.push_back ( std::make_pair<std::string, std::string> ( "About us", "web-site-about-us" ) );
    vTabs.push_back ( std::make_pair<std::string, std::string> ( "FAQ's", "web-site-faq" ) );
}

Constants gConstants;
