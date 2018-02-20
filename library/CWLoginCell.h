#ifndef CWLOGINCELL_H
#define CWLOGINCELL_H

#include <Wt/WContainerWidget>

class CWLoginCell : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWLoginCell ( std::string usrhash, Wt::WContainerWidget* parent = 0 );
};

#endif //CWLOGINCELL_H

