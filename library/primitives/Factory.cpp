#include "Factory.h"

#include <Wt/WContainerWidget>

#include "WTabs.h"
#include "WTableLayout.h"
#include "Title.h"
#include "Constants.h"

Wt::WWidget* Factory::Create ( IWidgetData * pWD, std::string str )
{
    if ( str == "WContainerWidget" )
        return new Wt::WContainerWidget();

    if ( str == "WTabs" )
        return new WTabs ( &gConstants.m_Tabs );

    if ( str == "Title" )
        return new Title();

    if ( str == "WTableLayout" )
        return new WTableLayout ( &gConstants.m_Table );

    return nullptr;
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
