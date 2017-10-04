#include "MainWidget.h"

#include <Wt/WText>

#include "../primitives/Factory.h"
#include "../primitives/CWSignals.h"

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
    this->addWidget ( Factory::Create ( "CWHeader", "SHeader" ) );
    this->addWidget ( Factory::Create ( "CWTableLayout", "STable" ) );
    this->addWidget ( Factory::Create ( "CWFooter", "SFooter" ) );

    gCWSignals.signallogintomainwidget.connect ( this, &MainWidget::UserLogin );

    gCWSignals.signalafterlogintomainwidget.connect ( std::bind ( [=]()
    {
        this->clear();
        this->addWidget ( Factory::Create ( "CWHeader", "SHeader" ) );
        this->addWidget ( Factory::Create ( "CWTableLayout", "STable" ) );
        this->addWidget ( Factory::Create ( "CWFooter", "SFooter" ) );
    } ) );
}

void MainWidget::UserLogin ( std::string s )
{
    this->clear();
    this->addWidget ( Factory::Create ( "CWHeader", "SHeader" ) );
    this->addWidget ( Factory::Create ( "CWTableLayout", "STableAfterLogin" ) );
    this->addWidget ( Factory::Create ( "CWFooter", "SFooter" ) );

    this->addWidget ( new Wt::WText ( s ) );
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
