#ifndef CWUSERLINEINPUT_H
#define CWUSERLINEINPUT_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWUserLineInput : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWUserLineInput ( IWidgetData * pD, void * payload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWUSERLINEINPUT_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
