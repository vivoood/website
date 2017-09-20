#include "Factory.h"

#include <Wt/WContainerWidget>

#include "CWTabs.h"
#include "CWTableLayout.h"
#include "CWHeader.h"
#include "Constants.h"

Wt::WWidget* Factory::Create ( std::string str )
{
    if ( str == "WContainerWidget" )
        return new Wt::WContainerWidget();

    if ( str == "WTabs" )
        return new CWTabs ( &gConstants.m_Tabs );

    if ( str == "CWHeader" )
        return new CWHeader();

    if ( str == "WTableLayout" )
        return new CWTableLayout ( &gConstants.m_Table );

    return nullptr;
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
