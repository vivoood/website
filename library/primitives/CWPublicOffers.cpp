#include "CWPublicOffers.h"

#include "Factory.h"

CWPublicOffers::CWPublicOffers ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffers * p = dynamic_cast<WidgetData::SOffers*> ( pD );
    if ( p != nullptr )
    {
        for ( unsigned int i = 0; i < p->m_Offers.size(); i++ )
        {
            this->addWidget ( Factory::Create ( "CWOffer", &p->m_Offers[i] ) );
        }
    }
}

