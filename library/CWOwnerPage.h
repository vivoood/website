#ifndef CWOWNERPAGE_H
#define CWOWNERPAGE_H

#include <Wt/WContainerWidget>

class CWOwnerPage : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOwnerPage ( std::string usrhash, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOWNERPAGE_H

