#include "CWAccount.h"

CWAccount::CWAccount ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SAccount * p = dynamic_cast<WidgetData::SAccount*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyle );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
