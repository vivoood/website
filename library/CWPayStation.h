#ifndef CWPAYSTATION_H
#define CWPAYSTATION_H

#include <Wt/WContainerWidget>

class CWPayStation : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWPayStation ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWPAYSTATION_H

