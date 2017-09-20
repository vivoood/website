#include "MainWidget.h"

#include "../primitives/CWHeader.h"
#include "../primitives/Factory.h"

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
    this->addWidget ( Factory::Create ( "CWHeader" ) );
    this->addWidget ( Factory::Create ( "CWTableLayout" ) );
    this->addWidget ( Factory::Create ( "CWFooter" ) );
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
