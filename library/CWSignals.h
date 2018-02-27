#ifndef CWSIGNALS_H
#define CWSIGNALS_H

#include <Wt/WSignal>
#include <string>

class CWSignals
{
public:
    Wt::Signal<std::string, std::string> signal_create_center_column;
};

extern CWSignals gCWSignals;

#endif // CWSIGNALS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
