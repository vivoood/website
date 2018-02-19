#include "CWAccount.h"

#include <Wt/WText>

CWAccount::CWAccount ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SAccount * p = dynamic_cast<WidgetData::SAccount*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyle );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWAccount can't get SAccount from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
