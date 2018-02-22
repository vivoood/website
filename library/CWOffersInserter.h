#ifndef CWOFFERSINSERTER_H
#define CWOFFERSINSERTER_H

#include <Wt/WContainerWidget>

class CWOffersInserter : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOffersInserter ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOFFERSINSERTER_H

