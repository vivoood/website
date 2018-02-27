#ifndef CWFAQ_H
#define CWFAQ_H

#include <Wt/WContainerWidget>

class CWFaq : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWFaq ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWFAQ_H

