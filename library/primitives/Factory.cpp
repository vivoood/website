#include "Factory.h"

#include <Wt/WContainerWidget>

#include "CWTabs.h"
#include "CWTableLayout.h"
#include "CWHeader.h"
#include "CWFooter.h"

#include "Constants.h"

Wt::WWidget* Factory::Create ( std::string str )
{
    if ( str == "WContainerWidget" )
        return new Wt::WContainerWidget();

    if ( str == "CWTabs" )
        return new CWTabs ( &gConstants.m_Tabs );

    if ( str == "CWHeader" )
        return new CWHeader( &gConstants.m_Header );

    if ( str == "CWTableLayout" )
        return new CWTableLayout ( &gConstants.m_Table );

    if ( str == "CWFooter" )
        return new CWFooter ( &gConstants.m_Footer );


    return nullptr;
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
