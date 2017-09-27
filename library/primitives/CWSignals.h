#ifndef CWSIGNALS_H
#define CWSIGNALS_H

#include <Wt/WSignal>

#include <string>

#include "IWidgetData.h"

class CWSignals
{
public:
    Wt::Signal<std::string, IWidgetData *> offertotab;
};

extern CWSignals gCWSignals;

#endif // CWSIGNALS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
