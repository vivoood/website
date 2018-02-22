#include "CWOwnerPage.h"

#include "Factory.h"

CWOwnerPage::CWOwnerPage ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( Factory::Create ( "CWOffersInserter", "owner/free_offers", usrhash ) );
    this->addWidget ( Factory::Create ( "CWOffersView", "owner/free_offers", usrhash ) );

    this->addWidget ( Factory::Create ( "CWOffersInserter", "owner/main_offers", usrhash ) );
    this->addWidget ( Factory::Create ( "CWOffersView", "owner/main_offers", usrhash ) );

    this->addWidget ( Factory::Create ( "CWOffersInserter", "owner/best_offers", usrhash ) );
    this->addWidget ( Factory::Create ( "CWOffersView", "owner/best_offers", usrhash ) );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
