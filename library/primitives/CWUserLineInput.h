#ifndef CWUSERLINEINPUT_H
#define CWUSERLINEINPUT_H

#include <Wt/WContainerWidget>

#include <sstream>

#include "IWidgetData.h"

class CWUserLineInput : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWUserLineInput ( IWidgetData * pD, std::stringstream &ss, Wt::WContainerWidget* parent = 0 );
};

#endif //CWUSERLINEINPUT_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
