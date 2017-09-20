#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>

#include "IWidgetData.h"

class Factory
{
public:
    static Wt::WWidget * Create ( std::string str, IWidgetData * pD = nullptr );
};

#endif // FACTORY_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
