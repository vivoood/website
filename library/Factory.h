#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>

#include "IWidgetData.h"
#include "Debug.h"

class Factory
{
    static Wt::WWidget * Create ( std::string strWidget, IWidgetData * pD );
public:
    static Wt::WWidget * Create ( std::string strWidget, std::string strData, std::string strHash );
};

#endif // FACTORY_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 






