#ifndef CWCHOOSECONTINENT_H
#define CWCHOOSECONTINENT_H

#include <Wt/WContainerWidget>

class CWChooseContinent : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWChooseContinent ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWCHOOSECONTINENT_H

