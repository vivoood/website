#include "CWPublicOffers.h"

#include <Wt/WText>

#include "Factory.h"
#include "CWHash.h"

CWPublicOffers::CWPublicOffers ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffersLeftRightBase * p = dynamic_cast<WidgetData::SOffersLeftRightBase*> ( pD );
    if ( p != nullptr )
    {
        for ( auto & i : p->m_OffersHashList )
        {
            this->addWidget ( Factory::Create ( "CWOffer", "SOffer", i ) );
        }
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWPublicOffers can't get SOffersLeftRightBase from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
