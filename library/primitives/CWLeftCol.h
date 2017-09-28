#ifndef CWLEFTCOL_H
#define CWLEFTCOL_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWLeftCol : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWLeftCol ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWLEFTCOL_H

