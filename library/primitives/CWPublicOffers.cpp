#include "CWPublicOffers.h"

#include <Wt/WText>

#include "Factory.h"
#include "CWHash.h"

CWPublicOffers::CWPublicOffers ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffers * p = dynamic_cast<WidgetData::SOffers*> ( pD );
    if ( p != nullptr )
    {
        for ( unsigned int i = 0; i < p->m_Offers.size(); i++ )
        {
            this->addWidget ( Factory::Create ( "CWOffer", CWHash::Get ( p->m_Offers[i].offerBig.strFrom + p->m_Offers[i].offerBig.strTo ), p->strHash ) );
        }
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWPublicOffers can't get SOffers from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
