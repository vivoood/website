#include "CWOffersView.h"

#include <Wt/WText>
#include <Wt/WPushButton>

#include "Debug.h"
#include "CWTable.h"
#include "CWUser.h"
#include "Factory.h"
#include "CWSignals.h"
#include "CWOfferDetailView.h"

CWOffersView::CWOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    OffersData fod ( strPayload );
    fod.load();

    for ( unsigned int i = 0; i < fod.vFreeOffers.size(); ++i )
    {
        CWTable * pTable = new CWTable();
        CWOfferDetailView * p = nullptr;

        OffersData::SOffer & o = fod.vFreeOffers[i];

        p = new CWOfferDetailView ( usrhash, "departure", o );
        pTable->elementAt ( 0, 0 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "arrival", o );
        pTable->elementAt ( 0, 1 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "price", o );
        pTable->elementAt ( 0, 2 )->addWidget ( p );

        p = new CWOfferDetailView ( usrhash, "options", o );
        pTable->elementAt ( 0, 3 )->addWidget ( p );

        Wt::WPushButton * del_buttton = new Wt::WPushButton ( "Delete" );
        del_buttton->clicked().connect ( std::bind ( [=]()
        {
            OffersData fod2 ( strPayload );
            fod2.del ( i );
            gCWSignals.signal_create_center_column.emit ( usrhash, strPayload );
        } ) );

        pTable->elementAt ( 0, 4 )->addWidget ( del_buttton );

        this->addWidget ( pTable );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
