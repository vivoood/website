#include "MainWidget.h"

#include "../Constants.h"
#include "../primitives/Title.h"

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
    this->addWidget ( new Title () );
    this->addWidget ( new Title () );
}

extern "C" Wt::WObject * create()
{
    return new MainWidget;
}

extern "C" void destroy ( Wt::WObject * p )
{
//     detele p;
}

