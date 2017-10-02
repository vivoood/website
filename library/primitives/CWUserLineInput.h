#ifndef CWUSERLINEINPUT_H
#define CWUSERLINEINPUT_H

#include <Wt/WContainerWidget>

#include <sstream>

#include "IWidgetData.h"

namespace Wt
{
class WText;
class WLineEdit;
}

class CWUserLineInput : public Wt::WContainerWidget
{
public:
    Wt::WText * pText = nullptr;
    Wt::WLineEdit * pEdit = nullptr;
private:
    friend class Factory;
    CWUserLineInput ( IWidgetData * pD, std::stringstream &ss, Wt::WContainerWidget* parent = 0 );
};

#endif //CWUSERLINEINPUT_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
