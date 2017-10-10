#ifndef CWQUERY_H
#define CWQUERY_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWQuery : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWQuery ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWQUERY_H

