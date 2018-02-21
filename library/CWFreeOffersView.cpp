#include "CWFreeOffersView.h"

#include <Wt/WText>

CWFreeOffersView::CWFreeOffersView ( std::string usrhash, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( new Wt::WText ("CWFreeOffersView") );
}

