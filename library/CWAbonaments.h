#ifndef CWABONAMENTS_H
#define CWABONAMENTS_H

#include <Wt/WContainerWidget>

class CWAbonaments : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWAbonaments ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
    
    std::vector<std::string> _abonaments = { "", "15 days", "", "30 days", "", "60 days", "", "90 days", "", "One year"  };
};

#endif //CWABONAMENTS_H

