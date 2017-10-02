#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>

#include "IWidgetData.h"

class Factory
{
public:
    static Wt::WWidget * Create ( std::string strWidget, std::string strData );
    static Wt::WWidget * Create ( std::string strWidget, std::string strData, std::stringstream &ss );
    static Wt::WWidget * Create ( std::string strWidget, IWidgetData * pD );
    static Wt::WWidget * Create ( std::string strWidget, IWidgetData * pD, std::stringstream &ss );
};

#endif // FACTORY_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 



