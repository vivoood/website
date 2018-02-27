#ifndef CWABONAMENTS_H
#define CWABONAMENTS_H

#include <Wt/WContainerWidget>

class CWAbonaments : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWAbonaments ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWABONAMENTS_H

