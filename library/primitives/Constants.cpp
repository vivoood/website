#include "Constants.h"

Constants::Constants()
{
    strSiteName.assign ( "Some Title" );
    strSiteSlogan.assign ( "use some slogan" );

    emptyTabData = { "n/a", "n/a", {"n/a"} };

    vTabs.push_back ( { "Home", "web-site-home", {"<p>Home page with common information</p>"} } );
    vTabs.push_back ( { "News", "web-site-news", {"<p>Here is any news </p>", "<th>air crashes </th>", "<th>ticket offers </th>"} } );
    vTabs.push_back ( { "Travel tips", "web-site-tips", {"<p>Make list</p>", "<p>Learn Common Phrases of the Local Language</p>", "<p>Always Buy Travel Insurance</p>", "<p>Pre-plan Your Outfits</p>", "<p>Stay Hydrated on Planes</p>"} } );
    vTabs.push_back ( { "Contacts", "web-site-contacts", {"<p>e-mail, phone, etc</p>"} } );
    vTabs.push_back ( { "About us", "web-site-about-us", {"<p>Little story</p>", "<p>Funny for us, maybe</p>"} } );
    vTabs.push_back ( { "FAQ's", "web-site-faq", {"<p>Frequently asked questions about air travel</p>"} } );
}

const Constants::STabData & Constants::FindTabData ( std::string strKey )
{
    for ( unsigned int i = 0; i < vTabs.size(); i++ )
    {
        if ( vTabs[i].strTabName == strKey )
        {
            return vTabs[i];
        }
    }

    return emptyTabData;
}

Constants gConstants;
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
