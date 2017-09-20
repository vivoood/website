#ifndef CWHEADER_H
#define CWHEADER_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWHeader : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWHeader ( IWidgetData * pD, WContainerWidget* parent = 0 );
};

#endif // CWHEADER_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
