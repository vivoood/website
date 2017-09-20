#include "CWFooter.h"

CWFooter::CWFooter ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SFooter * p = dynamic_cast<WidgetData::SFooter*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyle );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
