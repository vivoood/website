#include "CWOffersView.h"

#include <Wt/WText>

#include "CWTable.h"
#include "CWUser.h"
#include "Factory.h"
#include "Debug.h"

CWOffersView::CWOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    OffersData fod(strPayload);
    fod.load();

    std::vector<OffersData::SOffer> & vFreeOffers = fod.vFreeOffers;
    for ( unsigned int i = 0; i < vFreeOffers.size(); i++ )
    {
        CWTable *table = new CWTable();
        table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( Wt::WString ( "{1}" ).arg ( i + 1 ) ) );
        table->elementAt ( 0, 1 )->addWidget ( new Wt::WText ( vFreeOffers[i].departure ) );
        table->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( vFreeOffers[i].arrival ) );
        table->elementAt ( 0, 3 )->addWidget ( new Wt::WText ( vFreeOffers[i].cheap_price ) );
        table->elementAt ( 0, 4 )->addWidget ( new Wt::WText ( vFreeOffers[i].normal_price ) );
        this->addWidget ( table );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
