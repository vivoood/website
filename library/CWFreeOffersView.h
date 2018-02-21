#ifndef CWFREEOFFERSVIEW_H
#define CWFREEOFFERSVIEW_H

#include <Wt/WContainerWidget>

class CWFreeOffersView : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWFreeOffersView ( std::string usrhash, Wt::WContainerWidget* parent = 0 );
};

#endif //CWFREEOFFERSVIEW_H

