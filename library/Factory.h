#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>

#include "IWidgetData.h"
#include "Debug.h"

class Factory
{
public:
    static Wt::WWidget * Create ( std::string strWidget, std::string strUserHash );
};

#endif // FACTORY_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 






