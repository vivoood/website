#ifndef CWREGISTERACCOUNT_H
#define CWREGISTERACCOUNT_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

namespace Wt
{
class WLineEdit;
}

class CWRegisterAccount : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWRegisterAccount ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
    static std::string Validate ( Wt::WContainerWidget * pThis, Wt::WLineEdit * p, std::string name );
};

#endif //CWREGISTERACCOUNT_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
