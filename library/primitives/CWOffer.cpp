#include "CWOffer.h"

#include <Wt/WText>
#include <Wt/WBreak>

CWOffer::CWOffer ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffer * p = dynamic_cast<WidgetData::SOffer*> ( pD );
    if ( p != nullptr )
    {
        Wt::WContainerWidget * cont = new Wt::WContainerWidget ();
        this->setStyleClass ( p->strStyle );
        this->addWidget ( new Wt::WText ( p->strDirection ) );
        this->addWidget ( new Wt::WBreak () );
        this->addWidget ( new Wt::WText ( p->strPrice ) );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
