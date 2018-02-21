#include "CWOwnerPage.h"

#include "Factory.h"

CWOwnerPage::CWOwnerPage ( std::string usrhash, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( Factory::Create ( "CWFreeOffers", usrhash ) );
    this->addWidget ( Factory::Create ( "CWFreeOffersView", usrhash ) );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
