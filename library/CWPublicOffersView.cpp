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
#include "Debug.h"

CWPublicOffersView::CWPublicOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    std::string payload_header;
    GetPayloadHeader ( strPayload, payload_header );

    std::string payload_body;
    GetPayloadBody ( strPayload, payload_body );

    if ( payload_header == "show_free_offers_random" )
    {
        show_free_offers_random ();
    }
    else if ( payload_header == "show_best_offers" )
    {
        show_best_offers ();
    }
    else if ( payload_header == "continent" )
    {
        show_offers_by_continent ( payload_body );
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

void CWPublicOffersView::GetPayloadHeader ( const std::string & payload, std::string & result )
{
    int charid = payload.find ( ':' );
    if ( charid == std::string::npos )
    {
        result.assign ( payload );
    }
    else
    {
        result = payload.substr ( 0, charid );
    }
}

void CWPublicOffersView::GetPayloadBody ( const std::string & payload, std::string & result )
{
    int charid = payload.find ( ':' );
    if ( charid == std::string::npos )
    {
        result.assign ( payload );
    }
    else
    {
        result = payload.substr ( charid + 1 );
    }
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

void CWPublicOffersView::show_offers_by_continent ( const std::string & continent )
{
    OffersData ofdata ( "owner/free_offers" );
    ofdata.load();
    vOfData.clear();
    for ( auto it : ofdata.vFreeOffers )
    {
        if ( ( it._arrival_continent == continent ) || it._departure_continent == continent )
        {
            vOfData.push_back ( it );
        }
    }

    if ( ! vOfData.empty() )
    {
        std::random_shuffle ( vOfData.begin(), vOfData.end() );
        unsigned int uiElementCount = vOfData.size();
        uiShownElementsPerInstance = std::min ( uiElementCount, uiMaxFreeVisibleOffers );
        CreateView ( this, vOfData, uiShownElementsPerInstance );
    }
    else
    {
        this->addWidget ( new Wt::WText ( std::string ( "Can't find offer for " ) + continent ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
