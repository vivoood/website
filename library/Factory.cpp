#include "Factory.h"

#include <Wt/WContainerWidget>
#include <Wt/WText>

#include "CWCenterColumn.h"

Wt::WWidget* Factory::Create ( std::string strWidget, std::string strData, std::string strHash )
{
    return Factory::Create ( strWidget, nullptr );
}

Wt::WWidget* Factory::Create ( std::string strWidget, IWidgetData * pD )
{    
    if ( strWidget == "CWCenterColumn" )
        return new CWCenterColumn ( pD );

    return new Wt::WText ( "Factory could not create " + strWidget );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

