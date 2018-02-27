#ifndef CWHOWITWORKS_H
#define CWHOWITWORKS_H

#include <Wt/WContainerWidget>

class CWHowItWorks : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWHowItWorks ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWHOWITWORKS_H

