#include "MainWidget.h"

#include "CWTableLayout.h"

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
    CWTableLayout::TABLE t;
    t.push_back ( std::vector< std::string > { "FreeOffers" } );
    this->addWidget ( new CWTableLayout ( t, "n/a" ) );
}

extern "C" Wt::WObject * create()
{
    return new MainWidget;
}

extern "C" void destroy ( Wt::WObject * p )
{
    delete p;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
