#ifndef CWOWNERFREEOFFERS_H
#define CWOWNERFREEOFFERS_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWOwnerFreeOffers : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOwnerFreeOffers ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOWNERFREEOFFERS_H

