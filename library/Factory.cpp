#include "Factory.h"

#include <Wt/WContainerWidget>
#include <Wt/WText>

Wt::WWidget* Factory::Create ( std::string strWidget, std::string strData, std::string strHash )
{
    return Factory::Create ( strWidget, nullptr );
}

Wt::WWidget* Factory::Create ( std::string strWidget, IWidgetData * pD )
{    
    return new Wt::WText ( "n/a" );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
