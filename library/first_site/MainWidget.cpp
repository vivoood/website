#include "MainWidget.h"

#include "../primitives/Title.h"
#include "../primitives/WTabs.h"

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
    this->addWidget ( new Title () );
    this->addWidget( new WTabs() );
}

extern "C" Wt::WObject * create()
{
    return new MainWidget;
}

extern "C" void destroy ( Wt::WObject * p )
{
//     detele p;
}

