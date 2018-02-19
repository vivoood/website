#ifndef CWCOMBO_H
#define CWCOMBO_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

namespace Wt
{
class WText;
class WComboBox;
}

class CWCombo : public Wt::WContainerWidget
{
public:
    Wt::WText * pText = nullptr;
    Wt::WComboBox * pEdit = nullptr;
private:
    friend class Factory;
    CWCombo ( IWidgetData * pD, const std::string & label, const std::vector<std::string> & values, Wt::WContainerWidget* parent = 0 );
};

#endif //CWCOMBO_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
