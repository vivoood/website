#ifndef CWOFFERSVIEW_H
#define CWOFFERSVIEW_H

#include <Wt/WContainerWidget>

class CWOffersView : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent = 0 );
};

#endif //CWOFFERSVIEW_H
