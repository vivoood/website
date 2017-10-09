#ifndef CWRADIOBUTTONS_H
#define CWRADIOBUTTONS_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

namespace Wt
{
class WRadioButton;
class WText;
}

class CWRadioButtons : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWRadioButtons ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );

    Wt::WButtonGroup * group = nullptr;
    Wt::WText *outMsg = nullptr;
    void Click ( Wt::WRadioButton *selection );
    WidgetData::SRadioButtons * p = nullptr;
};

#endif //CWRADIOBUTTONS_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
