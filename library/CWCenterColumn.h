#ifndef CWCENTERCOLUMN_H
#define CWCENTERCOLUMN_H

#include <Wt/WContainerWidget>

class CWCenterColumn : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWCenterColumn ( std::__cxx11::string usrhash, Wt::WContainerWidget* parent = 0 );
};

#endif //CWCENTERCOLUMN_H

