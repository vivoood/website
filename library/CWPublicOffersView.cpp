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
    if ( strPayload == "show_free_offers_random" )
    {
        show_free_offers_random ();
    }
    else if ( strPayload == "show_best_offers" )
    {
        show_best_offers ();
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
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );
//         pTable->elementAt ( i, 0 )->addWidget ( new Wt::WText ( v[i].departure ) );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );

        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );
//         pTable->elementAt ( i, 1 )->addWidget ( new Wt::WText ( v[i].arrival ) );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 1 )->addWidget ( new Wt::WBreak() );

        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );
//         pTable->elementAt ( i, 2 )->addWidget ( new Wt::WText ( "$" + v[i].cheap_price ) );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 2 )->addWidget ( new Wt::WBreak() );

        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );
//         pTable->elementAt ( i, 3 )->addWidget ( new Wt::WText ( "$" + v[i].normal_price ) );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );
        pTable->elementAt ( i, 3 )->addWidget ( new Wt::WBreak() );


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
