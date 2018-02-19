#ifndef CWCENTERCOLUMN_H
#define CWCENTERCOLUMN_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWCenterColumn : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWCenterColumn ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWCENTERCOLUMN_H

