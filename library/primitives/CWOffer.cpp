#include "CWOffer.h"

#include <Wt/WImage>
#include <Wt/WLink>
#include <Wt/WText>

class MyImage : public Wt::WContainerWidget
{
public:
    MyImage ( std::string picid, std::string picstyle, Wt::WContainerWidget* parent = 0 )
    {
        Wt::WImage * pic = new Wt::WImage ( Wt::WLink ( picid ) );
        pic->setStyleClass ( picstyle );
        this->addWidget ( pic );
    }
};

CWOffer::CWOffer ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffer * p = dynamic_cast<WidgetData::SOffer*> ( pD );
    if ( p != nullptr )
    {
        MyImage * pic = new MyImage ( p->strPicAndStyle.first, p->strPicAndStyle.second );

        Wt::WContainerWidget * cont = new Wt::WContainerWidget ();
        cont->setStyleClass ( p->strStyle );
        cont->addWidget ( new Wt::WText ( p->strDirection ) );
        cont->addWidget ( new Wt::WText ( p->strPrice ) );
        cont->addWidget ( new Wt::WText ( p->strAirline ) );
        cont->addWidget ( new Wt::WText ( p->bDirectFlight ? " Direction flight" : " Flight with dislocation" ) );
        cont->addWidget ( new Wt::WText ( p->bOneWay ? " One-way ticket" : " Two-way ticket" ) );

        pic->addWidget ( cont );

        this->addWidget ( pic );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

