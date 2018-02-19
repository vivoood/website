#ifndef CWOWNERSETTINGS_H
#define CWOWNERSETTINGS_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWOwnerSettings : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOwnerSettings ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOWNERSETTINGS_H

