#include "CWOffersInserter.h"

#include <Wt/WText>
#include <Wt/WPushButton>

#include "CWUser.h"
#include "CWTable.h"
#include "CWLineEditField.h"
#include "CWOfferDetailView.h"
#include "CWSignals.h"

CWOffersInserter::CWOffersInserter ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    CWTable * pTable = new CWTable();

    if ( strPayload == "owner/free_offers" )
        pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Add FREE offers" ) );
    else if ( strPayload == "owner/main_offers" )
        pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Add MAIN offers" ) );
    else if ( strPayload == "owner/best_offers" )
        pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Add BEST offers" ) );
    else
        pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Title is not set" ) );

    CWOfferDetailView * pDet = new CWOfferDetailView ( usrhash, strPayload );
    pTable->elementAt ( 1, 0 )->addWidget ( pDet );

    this->addWidget ( pTable );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
