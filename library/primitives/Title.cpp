#include "Title.h"

#include "Constants.h"

#include <Wt/WTemplate>
#include <Wt/WText>

Title::Title ( Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WTemplate *templ = new Wt::WTemplate ( Wt::WString::tr ( "web-site-name-template" ) );
    templ->bindWidget ( "web-site-name", new Wt::WText ( gConstants.strSiteName ) );
    templ->bindWidget ( "web-site-slogan", new Wt::WText ( gConstants.strSiteSlogan ) );
    this->addWidget ( templ );
}
