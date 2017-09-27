#include "Factory.h"

#include <Wt/WContainerWidget>
#include <Wt/WText>

#include "CWFooter.h"
#include "CWHeader.h"
#include "CWOffer.h"
#include "CWPublicOffers.h"
#include "CWTableLayout.h"
#include "CWTabs.h"
#include "CWFAQ.h"
#include "CWContacts.h"
#include "CWOfferBig.h"

#include "Constants.h"

Wt::WWidget* Factory::Create ( std::string str, IWidgetData * pD )
{
    if ( str == "WContainerWidget" )
        return new Wt::WContainerWidget();

    if ( str == "CWTabs" )
        return new CWTabs ( &gConstants.m_Tabs );

    if ( str == "CWHeader" )
        return new CWHeader ( &gConstants.m_Header );

    if ( str == "CWTableLayout" )
        return new CWTableLayout ( &gConstants.m_Table );

    if ( str == "CWFooter" )
        return new CWFooter ( &gConstants.m_Footer );

    if ( str == "CWOffer" )
        return new CWOffer ( pD );

    if ( str == "CWFAQ" )
        return new CWFAQ ( pD );

    if ( str == "CWPublicOffers" )
        return new CWPublicOffers ( &gConstants.m_Offers );

    if ( str == "CWContacts" )
        return new CWContacts ( pD );

    if ( str == "CWOfferBig" )
        return new CWOfferBig ( pD );

    return new Wt::WText ( "n/a" );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
