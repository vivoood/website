#ifndef CWCENTERCOLUMN_H
#define CWCENTERCOLUMN_H

#include <Wt/WContainerWidget>

class CWCenterColumn : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWCenterColumn ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWCENTERCOLUMN_H

