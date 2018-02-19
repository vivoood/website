#ifndef ENTRYONE_H
#define ENTRYONE_H

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include "IWidgetData.h"

class EntryOne : public Wt::WContainerWidget
{
public:
    friend class Factory;
    EntryOne ( Wt::WApplication * pApp );
};

#endif // ENTRYONE_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
