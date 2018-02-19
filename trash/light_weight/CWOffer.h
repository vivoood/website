#ifndef CWOFFER_H
#define CWOFFER_H

#include <Wt/WContainerWidget>

class CWOffer : public Wt::WContainerWidget
{
public:
    CWOffer ( std::string & strHash, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOFFER_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
