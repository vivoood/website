#include "Factory.h"

#include <Wt/WContainerWidget>

#include "WTabs.h"
#include "WTableLayout.h"
#include "Title.h"

Wt::WWidget* Factory::Create ( std::string str )
{
    if ( str == "WContainerWidget" )
        return new Wt::WContainerWidget();

    if ( str == "WTabs" )
        return new WTabs();

    if ( str == "Title" )
        return new Title();

    return nullptr;
}
