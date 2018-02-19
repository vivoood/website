#ifndef CWDREAMTEAM_H
#define CWDREAMTEAM_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWDreamTeam : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWDreamTeam ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //CWDREAMTEAM_H

