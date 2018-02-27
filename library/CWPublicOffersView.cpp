#include "CWPublicOffersView.h"

#include <algorithm>

#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WTimer>
#include <Wt/WCssDecorationStyle>

#include "CWTable.h"
#include "Factory.h"
#include "CWUser.h"
#include "CWOfferDetailView.h"

CWPublicOffersView::CWPublicOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    if ( strPayload == "show_free_offers_random" )
    {
        show_free_offers_random ();
    }
    else if ( strPayload == "show_best_offers" )
    {
        show_best_offers ();
    }
    else if ( strPayload == "Africa" )
    {
        this->addWidget ( new Wt::WText ( "AAAAAAAAAA" ) );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWPublicOffersView - Can't recognize payload" ) );
    }
}

void CWPublicOffersView::CreateView ( Wt::WContainerWidget * p, std::vector<OffersData::SOffer> & v, unsigned int uiShownElements )
{
    p->clear();

    CWTable * pTable = new CWTable();

    for ( int i = 0; i < uiShownElements; ++i )
    {
        CWTable * pTable = new CWTable();
        CWOfferDetailView * p = nullptr;

        p = new CWOfferDetailView ( "no_hash_public_offers", "departure", v[i] );
        pTable->elementAt ( 0, 0 )->addWidget ( p );

        p = new CWOfferDetailView ( "no_hash_public_offers", "arrival", v[i] );
        pTable->elementAt ( 0, 1 )->addWidget ( p );

        p = new CWOfferDetailView ( "no_hash_public_offers", "price", v[i] );
        pTable->elementAt ( 0, 2 )->addWidget ( p );

        p = new CWOfferDetailView ( "no_hash_public_offers", "options", v[i] );
        pTable->elementAt ( 0, 3 )->addWidget ( p );

        this->addWidget ( pTable );
    }

    p->addWidget ( pTable );
}

void CWPublicOffersView::show_free_offers_random ()
{
    this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/tmpbgr.png" ) );

    OffersData ofdata ( "owner/free_offers" );
    ofdata.load();

    vOfData = ofdata.vFreeOffers;

    std::random_shuffle ( vOfData.begin(), vOfData.end() );
    unsigned int uiElementCount = vOfData.size();
    uiShownElementsPerInstance = std::min ( uiElementCount, uiMaxFreeVisibleOffers );
    CreateView ( this, vOfData, uiShownElementsPerInstance );

    Wt::WTimer * t = new Wt::WTimer ( this );
    t->setInterval ( nChangeTimeDuration );
    t->start();
    t->timeout().connect ( std::bind ( [&]()
    {
        std::random_shuffle ( vOfData.begin(), vOfData.end() );
        unsigned int uiElementCount = vOfData.size();
        uiShownElementsPerInstance = std::min ( uiElementCount, uiMaxFreeVisibleOffers );
        CreateView ( this, vOfData, uiShownElementsPerInstance );
    } ) );
}

void CWPublicOffersView::show_best_offers ()
{
    this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/tmpbgr.png" ) );

    this->addWidget ( new Wt::WText ( "Top 5 best deals" ) );

    OffersData ofdata ( "owner/best_offers" );
    ofdata.load();

    vOfData = ofdata.vFreeOffers;
    unsigned int uiElementCount = vOfData.size();
    uiShownElementsPerInstance = std::min ( uiElementCount, uiMaxFreeVisibleOffers );
    CreateView ( this, vOfData, uiShownElementsPerInstance );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
