#include "Factory.h"

#include <Wt/WContainerWidget>
#include <Wt/WText>

#include "FreeOffers.h"

Wt::WWidget* Factory::Create ( std::string strWidget, std::string strHash )
{
    if ( strWidget == "WContainerWidget" )
        return new Wt::WContainerWidget();

    if ( strWidget == "FreeOffers" )
        return new FreeOffers ( strHash );

    return new Wt::WText ( "n/a" );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
