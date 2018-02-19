#ifndef CWQUERY_H
#define CWQUERY_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWQuery : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWQuery ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
    void Create ( Wt::WContainerWidget * c, Wt::WContainerWidget * m, IWidgetData * pD );
    Wt::WContainerWidget * container = nullptr;
    Wt::WContainerWidget * outmsg = nullptr;
};

#endif //CWQUERY_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
