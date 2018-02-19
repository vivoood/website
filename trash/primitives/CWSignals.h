#ifndef CWSIGNALS_H
#define CWSIGNALS_H

#include <Wt/WSignal>

#include <string>

#include "IWidgetData.h"

class CWSignals
{
public:
    Wt::Signal<std::string, std::string, std::string> signaloffertotab;
    Wt::Signal<std::string> signallogintomainwidget;
    Wt::Signal<std::string, std::string, std::string> signallogintotabs;
    Wt::Signal<void> signalafterlogintomainwidget;
};

extern CWSignals gCWSignals;

#endif // CWSIGNALS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
