#include "MainWidget.h"

#include "../primitives/Factory.h"

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
    this->addWidget ( Factory::Create ( "CWOwnerFreeOffers", "SOwnerFreeOffers", "my-name" ) );
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
