#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>

#include "IWidgetData.h"

class Factory
{
public:
    static Wt::WWidget * Create ( IWidgetData * pWD, std::string str );
};

#endif // FACTORY_H
