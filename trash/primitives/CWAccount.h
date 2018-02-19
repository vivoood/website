#ifndef CWACCOUNT_H
#define CWACCOUNT_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWAccount : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWAccount ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWACCOUNT_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
