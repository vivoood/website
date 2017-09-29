#ifndef CWREGISTERACCOUNT_H
#define CWREGISTERACCOUNT_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWRegisterAccount : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWRegisterAccount ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWREGISTERACCOUNT_H

