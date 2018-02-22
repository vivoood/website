#include "CWPublicOffersView.h"

#include <algorithm>

#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WTimer>
#include <Wt/WCssDecorationStyle>

#include "CWTable.h"
#include "Factory.h"
#include "CWUser.h"

CWPublicOffersView::CWPublicOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/tmpbgr.png" ) );

    if ( strPayload == "show_free_offers_random" )
    {
        OffersData ofdata ( "owner/free_offers" );
        ofdata.load();

        vOfData = ofdata.vFreeOffers;
        CreateView ( this, vOfData );

        Wt::WTimer * t = new Wt::WTimer ( this );
        t->setInterval ( nChangeTimeDuration );
        t->start();
        t->timeout().connect ( std::bind ( [&]()
        {
            CreateView ( this, vOfData );
        } ) );
    }
}

void CWPublicOffersView::CreateView ( Wt::WContainerWidget * p, std::vector<OffersData::SOffer> & v )
{
    p->clear();

    std::random_shuffle ( v.begin(), v.end() );

    CWTable * pTable = new CWTable();

    unsigned int uiElementCount = v.size();
    for ( int i = 0; i < std::min ( uiElementCount, uiMaxVisibleOffers ); ++i )
    {
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WText ( v[i].departure ) );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );

        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WText ( v[i].arrival ) );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );

        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WText ( "$" + v[i].cheap_price ) );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );

        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WText ( "$" + v[i].normal_price ) );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );


    }
    p->addWidget ( pTable );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
