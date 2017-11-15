#ifndef CWOWNERCONTAINER_H
#define CWOWNERCONTAINER_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWOwnerContainer : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOwnerContainer ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOWNERCONTAINER_H

