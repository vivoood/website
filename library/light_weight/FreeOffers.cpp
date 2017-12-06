#include "FreeOffers.h"

#include <Wt/WText>

#include "CWOwnerData.h"
#include "CWOffer.h"

FreeOffers::FreeOffers ( std::string strHash, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    CWOwnerData d;
    d.LoadFreeOffers();
    std::vector< std::string > v = d.GetFreeOffers();
    for ( auto & i : v )
        this->addWidget ( new CWOffer ( i ) );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

