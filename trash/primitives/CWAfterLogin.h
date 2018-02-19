#ifndef CWAFTERLOGIN_H
#define CWAFTERLOGIN_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWAfterLogin : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWAfterLogin ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWAFTERLOGIN_H

