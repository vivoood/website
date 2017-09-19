#include "Constants.h"

#include "WTabs.h"

Constants::Constants()
{
    strSiteName.assign ( "Some Title" );
    strSiteSlogan.assign ( "use some slogan" );

    emptyTabData = { "n/a", "n/a", {"n/a"} };

    vMenuButtons.push_back ( { "Home", "web-site-home", {"<p>Home page with common information</p>"} } );
    vMenuButtons.push_back ( { "News", "web-site-news", {"<p>Here is any news </p>", "<th>air crashes </th>", "<th>ticket offers </th>"} } );
    vMenuButtons.push_back ( { "Travel tips", "web-site-tips", {"<p>Make list</p>", "<p>Learn Common Phrases of the Local Language</p>", "<p>Always Buy Travel Insurance</p>", "<p>Pre-plan Your Outfits</p>", "<p>Stay Hydrated on Planes</p>"} } );
    vMenuButtons.push_back ( { "Contacts", "web-site-contacts", {"<p>e-mail, phone, etc</p>"} } );
    vMenuButtons.push_back ( { "About us", "web-site-about-us", {"<p>Little story</p>", "<p>Funny for us, maybe</p>"} } );
    vMenuButtons.push_back ( { "FAQ's", "web-site-faq", {"<p>Frequently asked questions about air travel</p>"} } );

    vTable.push_back ( { { "table-col-1", "15%", "WContainerWidget" }, { "table-col-2", "65%", "WTabs" }, { "table-col-3", "20%", "WContainerWidget" } } );
}

const Constants::STabButtonsData & Constants::FindTabData ( std::string strKey )
{
    for ( unsigned int i = 0; i < vMenuButtons.size(); i++ )
    {
        if ( vMenuButtons[i].strTabName == strKey )
        {
            return vMenuButtons[i];
        }
    }

    return emptyTabData;
}

Constants gConstants;
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

