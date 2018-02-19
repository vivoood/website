#ifndef CWOWNERFREEOFFERSVIEW_H
#define CWOWNERFREEOFFERSVIEW_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWOwnerFreeOffersView : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOwnerFreeOffersView ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOWNERFREEOFFERSVIEW_H

