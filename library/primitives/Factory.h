#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>

#include "IWidgetData.h"

class Factory
{
public:
    static Wt::WWidget * Create ( std::string strWidget, std::string strData, void * payload = nullptr );
    static Wt::WWidget * Create ( std::string strWidget, IWidgetData * pD, void * payload = nullptr );
};

#endif // FACTORY_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 



