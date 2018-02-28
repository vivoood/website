#include "CWOffersView.h"

#include <Wt/WText>
#include <Wt/WPushButton>

#include "CWTable.h"
#include "CWUser.h"
#include "Factory.h"
#include "CWSignals.h"
#include "CWOfferDetailView.h"

CWOffersView::CWOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    OffersData fod ( strPayload );
    fod.load();

    for( std::vector<OffersData::SOffer>::iterator it = fod.vFreeOffers.begin(); it != fod.vFreeOffers.end(); ++it )
    {
        CWTable * pTable = new CWTable();
        CWOfferDetailView * p = nullptr;

        p = new CWOfferDetailView ( usrhash, "departure", *it );
        pTable->elementAt ( 0, 0 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "arrival", *it );
        pTable->elementAt ( 0, 1 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "price", *it );
        pTable->elementAt ( 0, 2 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "options", *it );
        pTable->elementAt ( 0, 3 )->addWidget ( p );

        Wt::WPushButton * del_buttton = new Wt::WPushButton ( "Delete" );
//         del_buttton->clicked().connect ( std::bind ( [&]()
//         {
//             fod.del ( it );
//             gCWSignals.signal_create_center_column.emit ( usrhash, strPayload );
//         } ) );

        pTable->elementAt ( 0, 4 )->addWidget ( del_buttton );

        this->addWidget ( pTable );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
