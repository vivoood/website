#ifndef CWOFFER_H
#define CWOFFER_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWOffer : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOffer ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOFFER_H

