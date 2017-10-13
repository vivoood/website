#ifndef CWMYQUERIES_H
#define CWMYQUERIES_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWMyQueries : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWMyQueries ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWMYQUERIES_H

