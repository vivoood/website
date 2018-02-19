#ifndef CWLOGIN_H
#define CWLOGIN_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWLogin : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWLogin ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWLOGIN_H

