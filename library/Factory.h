#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>
#include <Wt/WContainerWidget>

#include "Debug.h"

class Factory
{
public:
    static Wt::WWidget * Create ( std::string strWidget, std::string strWidgetPayload, std::string strUserHash, Wt::WContainerWidget * parent = nullptr );
};

#endif // FACTORY_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
