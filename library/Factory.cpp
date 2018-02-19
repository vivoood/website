#include "Factory.h"

#include <Wt/WContainerWidget>
#include <Wt/WText>

#include "CWCenterColumn.h"

Wt::WWidget* Factory::Create ( std::string strWidget, std::string strUserHash )
{
    if ( strWidget == "CWCenterColumn" )
        return new CWCenterColumn ( strUserHash );

    return new Wt::WText ( "Factory could not create " + strWidget );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

