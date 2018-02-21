#ifndef CWFREEOFFERS_H
#define CWFREEOFFERS_H

#include <Wt/WContainerWidget>

class CWFreeOffers : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWFreeOffers ( std::string usrhash, Wt::WContainerWidget* parent = 0 );
};

#endif //CWFREEOFFERS_H

