#include "CWOfferBig.h"

#include <Wt/WText>

CWOfferBig::CWOfferBig ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOfferBig * p = dynamic_cast<WidgetData::SOfferBig*> ( pD );
    if ( p != nullptr )
    {
        this->addWidget ( new Wt::WText ( p->strStyle ) );
        this->addWidget ( new Wt::WText ( p->strFrom ) );
        this->addWidget ( new Wt::WText ( p->strTo ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
