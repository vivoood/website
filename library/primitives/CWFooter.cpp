#include "CWFooter.h"

#include <Wt/WText>

CWFooter::CWFooter ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SFooter * p = dynamic_cast<WidgetData::SFooter*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyle );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWFooter can't get SFooter from IWidgetData for user: " + pD->strHash ) );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
