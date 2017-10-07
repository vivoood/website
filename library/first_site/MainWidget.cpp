#include "MainWidget.h"

#include <Wt/WText>

#include "../primitives/Factory.h"
#include "../primitives/CWSignals.h"
#include "../primitives/CWUser.h"

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
//     this->addWidget ( Factory::Create ( "CWAccount", "SMyAccount", "ivaylo" ) );
//     return;
    
    
    this->addWidget ( Factory::Create ( "CWHeader", "SHeader", "n/a" ) );
    this->addWidget ( Factory::Create ( "CWTableLayout", "STable", "n/a" ) );
    this->addWidget ( Factory::Create ( "CWFooter", "SFooter", "n/a" ) );

    gCWSignals.signallogintomainwidget.connect ( this, &MainWidget::UserLogin );

    gCWSignals.signalafterlogintomainwidget.connect ( std::bind ( [=]()
    {
        this->clear();
        this->addWidget ( Factory::Create ( "CWHeader", "SHeader", "n/a" ) );
        this->addWidget ( Factory::Create ( "CWTableLayout", "STable", "n/a" ) );
        this->addWidget ( Factory::Create ( "CWFooter", "SFooter", "n/a" ) );
    } ) );
}

void MainWidget::UserLogin ( std::string strHash )
{
    this->clear();

    if ( CWUser::CheckOwner ( strHash ) )
    {
        this->addWidget ( Factory::Create ( "CWTableLayout", "STableOwnerLogin", strHash ) );
        return;
    }

    this->addWidget ( Factory::Create ( "CWHeader", "SHeader", strHash ) );
    this->addWidget ( Factory::Create ( "CWTableLayout", "STableAfterLogin", strHash ) );
    this->addWidget ( Factory::Create ( "CWFooter", "SFooter", strHash ) );
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
