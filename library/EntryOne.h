#ifndef ENTRYONE_H
#define ENTRYONE_H

#include <Wt/WContainerWidget>
#include "IWidgetData.h"

class EntryOne : public Wt::WContainerWidget
{
public:
    friend class Factory;
    EntryOne ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif // ENTRYONE_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
