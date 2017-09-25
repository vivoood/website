#ifndef CWFAQ_H
#define CWFAQ_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWFAQ : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWFAQ ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWFAQ_H

