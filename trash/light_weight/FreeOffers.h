#ifndef FREEOFFERS_H
#define FREEOFFERS_H

#include <Wt/WContainerWidget>

class FreeOffers : public Wt::WContainerWidget
{
public:
    FreeOffers ( std::string strHash, Wt::WContainerWidget* parent = 0 );
};

#endif // FREEOFFERS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
