#ifndef CWTABS_H
#define CWTABS_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWTabs : public Wt::WContainerWidget
{
public:
    CWTabs ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif // CWTABS_H
