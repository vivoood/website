#include "CWOffersView.h"

#include <Wt/WText>

#include "CWTable.h"
#include "CWUser.h"
#include "Factory.h"
#include "Debug.h"
#include "CWOfferDetailView.h"

CWOffersView::CWOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    OffersData fod ( strPayload );
    fod.load();

    std::vector<OffersData::SOffer> & vFreeOffers = fod.vFreeOffers;
    for ( auto & it : vFreeOffers )
    {
        CWTable * pTable = new CWTable();
        CWOfferDetailView * p = nullptr;

        p = new CWOfferDetailView ( usrhash, "departure", it );
        pTable->elementAt ( 0, 0 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "arrival", it );
        pTable->elementAt ( 0, 1 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "price", it );
        pTable->elementAt ( 0, 2 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "options", it );
        pTable->elementAt ( 0, 3 )->addWidget ( p );

        this->addWidget ( pTable );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


