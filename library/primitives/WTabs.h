#ifndef WTABS_H
#define WTABS_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class WTabs : public Wt::WContainerWidget
{
public:
    WTabs ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif // WTABS_H
