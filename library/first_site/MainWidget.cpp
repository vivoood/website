#include "MainWidget.h"

#include "../primitives/Title.h"
#include "../primitives/WTabs.h"
#include "../primitives/WTableLayout.h"

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
    this->addWidget ( new Title () );
//     this->addWidget( new WTabs() );
    this->addWidget ( new WTableLayout() );
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
