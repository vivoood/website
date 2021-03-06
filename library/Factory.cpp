#include "Factory.h"

#include <Wt/WText>

#include "CWCenterColumn.h"
#include "CWLoginCell.h"
#include "CWIntroPage.h"
#include "CWSignIn.h"
#include "CWOwnerPage.h"
#include "CWOffersInserter.h"
#include "CWOffersView.h"
#include "CWPublicOffersView.h"
#include "CWChooseContinent.h"
#include "CWHowItWorks.h"
#include "CWFaq.h"
#include "CWAbonaments.h"
#include "CWPayStation.h"

Wt::WWidget * Factory::Create ( std::string strWidget, std::string strWidgetPayload, std::string strUserHash, Wt::WContainerWidget * parent )
{
    if ( strWidget == "CWCenterColumn" )
        return new CWCenterColumn ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWLoginCell" )
        return new CWLoginCell ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWIntroPage" )
        return new CWIntroPage ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWSignIn" )
        return new CWSignIn ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWOwnerPage" )
        return new CWOwnerPage ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWOffersInserter" )
        return new CWOffersInserter ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWOffersView" )
        return new CWOffersView ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWPublicOffersView" )
        return new CWPublicOffersView ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWChooseContinent" )
        return new CWChooseContinent ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWHowItWorks" )
        return new CWHowItWorks ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWFaq" )
        return new CWFaq ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWAbonaments" )
        return new CWAbonaments ( strUserHash, strWidgetPayload, parent );

    if ( strWidget == "CWPayStation" )
        return new CWPayStation ( strUserHash, strWidgetPayload, parent );

    return new Wt::WText ( "Factory could not create " + strWidget );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


