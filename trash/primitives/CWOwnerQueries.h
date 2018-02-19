#ifndef CWOWNERQUERIES_H
#define CWOWNERQUERIES_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWOwnerQueries : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOwnerQueries ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOWNERQUERIES_H

