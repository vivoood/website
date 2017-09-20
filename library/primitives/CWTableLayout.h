/*
 * Velislav Velkov
 */

#ifndef WTABLELAYOUT_H
#define WTABLELAYOUT_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWTableLayout  : public Wt::WContainerWidget
{
public:
    CWTableLayout ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif // WTABLELAYOUT_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
