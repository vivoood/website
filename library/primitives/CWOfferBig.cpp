#include "CWOfferBig.h"

#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WText>
#include <Wt/WBreak>

CWOfferBig::CWOfferBig ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOfferBig * p = dynamic_cast<WidgetData::SOfferBig*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyle );

        this->addWidget ( new Wt::WText ( "From " + p->strFrom + " to " + p->strTo ) );
        this->addWidget ( new Wt::WBreak() );

        this->addWidget ( new Wt::WText ( "Airline is " + p->strAirline ) );
        this->addWidget ( new Wt::WBreak() );

        this->addWidget ( new Wt::WText ( "Only for " + p->strPrice ) );
        this->addWidget ( new Wt::WBreak() );

        this->addWidget ( new Wt::WText ( "Ticket is " + std::string ( p->bOneWay ? "One way" : "Two way" ) ) );
        this->addWidget ( new Wt::WBreak() );

        this->addWidget ( new Wt::WText ( "Flight " + std::string ( p->bDirectFlight ? "is direct" : "need a jump" ) ) );
        this->addWidget ( new Wt::WBreak() );

        Wt::WAnchor * pAnchor = new Wt::WAnchor ( Wt::WLink ( p->strHyperlink ), "buy a ticket from the seller" );
        this->addWidget ( pAnchor );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

