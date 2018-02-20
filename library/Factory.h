#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>
#include <Wt/WContainerWidget>

#include "IWidgetData.h"
#include "Debug.h"

class Factory
{
public:
    static Wt::WWidget * Create ( std::string strWidget, std::string strUserHash, Wt::WContainerWidget * parent = nullptr );
};

#endif // FACTORY_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 






