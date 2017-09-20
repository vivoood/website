#ifndef CWPUBLICOFFERS_H
#define CWPUBLICOFFERS_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWPublicOffers : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWPublicOffers ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWPUBLICOFFERS_H

