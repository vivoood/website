#ifndef CWFOOTER_H
#define CWFOOTER_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWFooter : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWFooter ( IWidgetData * pD, WContainerWidget* parent = 0 );
};

#endif // CWFOOTER_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
