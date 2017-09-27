#ifndef CWOFFERBIG_H
#define CWOFFERBIG_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWOfferBig : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOfferBig ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOFFERBIG_H

