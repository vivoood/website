#include "MainWidget.h"

#include "../Constants.h"

#include <Wt/WTemplate>
#include <Wt/WText>

MainWidget::MainWidget ( Wt::WContainerWidget* perant ) : WContainerWidget ( perant )
{
    Wt::WTemplate *templ = new Wt::WTemplate ( Wt::WString::tr ( "web-site-name-template" ) );
    templ->bindWidget ( "web-site-name", new Wt::WText ( strSiteName ) );
    templ->bindWidget ( "web-site-slogan", new Wt::WText ( strSiteSlogan ) );
    this->addWidget(templ);
}

extern "C" Wt::WObject * create()
{
    return new MainWidget;
}

extern "C" void destroy ( Wt::WObject * p )
{
//     detele p;
}

