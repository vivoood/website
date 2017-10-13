#include "CWMyQueries.h"

CWMyQueries::CWMyQueries ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SMyQueries * p = dynamic_cast<WidgetData::SMyQueries*> ( pD );
    if ( p != nullptr )
    {

    }
}

