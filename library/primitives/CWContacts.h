#ifndef CWCONTACTS_H
#define CWCONTACTS_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWContacts : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWContacts ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
    void f(int, std::string);
};

#endif //CWCONTACTS_H



