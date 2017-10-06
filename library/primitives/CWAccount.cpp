#include "CWAccount.h"

#include <Wt/WText>
#include <Wt/WBreak>

CWAccount::CWAccount ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SAccount * p = dynamic_cast<WidgetData::SAccount*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyle );
        this->addWidget ( new Wt::WText ( "content" ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
