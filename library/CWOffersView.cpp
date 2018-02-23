#include "CWOffersView.h"

#include <Wt/WText>

#include "CWTable.h"
#include "CWUser.h"
#include "Factory.h"
#include "Debug.h"

CWOffersView::CWOffersView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    OffersData fod ( strPayload );
    fod.load();

    std::vector<OffersData::SOffer> & vFreeOffers = fod.vFreeOffers;
    for ( unsigned int i = 0; i < vFreeOffers.size(); i++ )
    {
//         std::string _departure_continent = "unknown_departure_cont";
//         std::string _departure_city = "unknown_departure";
//         std::string _departure_code = "unknown_departure_code";
//         std::string _departure_date = "unknown_departure_date";
// 
//         std::string _arrival_continent = "unknown_arrival_cont";
//         std::string _arrival_city = "unknown_arrival";
//         std::string _arrival_code = "unknown_arrival_code";
//         std::string _arrival_date = "unknown_arrival_date";
// 
//         std::string _currency_code = "unknown_currency_code";
//         std::string _cheap_price = "unknown_price";
//         std::string _normal_price = "unknown_price";
// 
//         std::string _airline = "unknown_airline";
//         std::string _direction = "unknown_direction";
//         std::string _luggage = "unknown_luggage";
//         std::string _payload = "unknown_payload";

        CWTable *table = new CWTable();
//         table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( Wt::WString ( "{1}" ).arg ( i + 1 ) ) );
//         table->elementAt ( 0, 1 )->addWidget ( new Wt::WText ( vFreeOffers[i].departure ) );
//         table->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( vFreeOffers[i].arrival ) );
//         table->elementAt ( 0, 3 )->addWidget ( new Wt::WText ( vFreeOffers[i].cheap_price ) );
//         table->elementAt ( 0, 4 )->addWidget ( new Wt::WText ( vFreeOffers[i].normal_price ) );
        this->addWidget ( table );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
