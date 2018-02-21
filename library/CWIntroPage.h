#ifndef CWINTROPAGE_H
#define CWINTROPAGE_H

#include <Wt/WContainerWidget>

class CWIntroPage : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWIntroPage ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWINTROPAGE_H

