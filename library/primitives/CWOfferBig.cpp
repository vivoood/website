#include "CWOfferBig.h"

#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WText>
#include <Wt/WBreak>

CWOfferBig::CWOfferBig ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffer * p = dynamic_cast<WidgetData::SOffer*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->offerBig.strStyle );

        this->addWidget ( new Wt::WText ( "From " + p->offerBig.strFrom + " to " + p->offerBig.strTo ) );
        this->addWidget ( new Wt::WBreak() );

        this->addWidget ( new Wt::WText ( "Airline is " + p->offerBig.strAirline ) );
        this->addWidget ( new Wt::WBreak() );

        this->addWidget ( new Wt::WText ( "Only for " + p->offerBig.strPrice ) );
        this->addWidget ( new Wt::WBreak() );

        this->addWidget ( new Wt::WText ( "Ticket is " + std::string ( p->offerBig.bOneWay ? "One way" : "Two way" ) ) );
        this->addWidget ( new Wt::WBreak() );

        this->addWidget ( new Wt::WText ( "Flight " + std::string ( p->offerBig.bDirectFlight ? "is direct" : "need a jump" ) ) );
        this->addWidget ( new Wt::WBreak() );

        Wt::WAnchor * pAnchor = new Wt::WAnchor ( Wt::WLink ( p->offerBig.strHyperlink ), "buy a ticket from the seller" );
        this->addWidget ( pAnchor );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWOfferBig can't get SOffer from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

