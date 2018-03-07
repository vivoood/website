#include "CWOfferDetailView.h"

#include <Wt/WText>
#include <Wt/WPushButton>

#include "CWTable.h"
#include "CWSignals.h"
#include "CWLineEditField.h"

CWOfferDetailView::CWOfferDetailView ( std::string usrhash, std::string strPayload, OffersData::SOffer & offr, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    if ( strPayload == "departure" )
    {
        CWTable * pTable = new CWTable();
        pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Departure details" ) );

        pTable->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Continent" ) );
        pTable->elementAt ( 1, 1 )->addWidget ( new Wt::WText ( offr._departure_continent ) );

        pTable->elementAt ( 2, 0 )->addWidget ( new Wt::WText ( "City" ) );
        pTable->elementAt ( 2, 1 )->addWidget ( new Wt::WText ( offr._departure_city ) );

        pTable->elementAt ( 3, 0 )->addWidget ( new Wt::WText ( "Airport" ) );
        pTable->elementAt ( 3, 1 )->addWidget ( new Wt::WText ( offr._departure_code ) );

        pTable->elementAt ( 4, 0 )->addWidget ( new Wt::WText ( "Date" ) );
        pTable->elementAt ( 4, 1 )->addWidget ( new Wt::WText ( offr._departure_date ) );

        this->addWidget ( pTable );
    }
    else if ( strPayload == "arrival" )
    {
        CWTable * pTable = new CWTable();
        pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Arrival details" ) );

        pTable->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Continetn" ) );
        pTable->elementAt ( 1, 1 )->addWidget ( new Wt::WText ( offr._arrival_continent ) );

        pTable->elementAt ( 2, 0 )->addWidget ( new Wt::WText ( "City" ) );
        pTable->elementAt ( 2, 1 )->addWidget ( new Wt::WText ( offr._arrival_city ) );

        pTable->elementAt ( 3, 0 )->addWidget ( new Wt::WText ( "Airport" ) );
        pTable->elementAt ( 3, 1 )->addWidget ( new Wt::WText ( offr._arrival_code ) );

        pTable->elementAt ( 4, 0 )->addWidget ( new Wt::WText ( "Date" ) );
        pTable->elementAt ( 4, 1 )->addWidget ( new Wt::WText ( offr._arrival_date ) );
        this->addWidget ( pTable );
    }
    else if ( strPayload == "price" )
    {
        CWTable * pTable = new CWTable();
        pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Price details" ) );

        pTable->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Currency Code" ) );
        pTable->elementAt ( 1, 1 )->addWidget ( new Wt::WText ( offr._currency_code ) );

        pTable->elementAt ( 2, 0 )->addWidget ( new Wt::WText ( "Price" ) );
        pTable->elementAt ( 2, 1 )->addWidget ( new Wt::WText ( offr._cheap_price ) );

        pTable->elementAt ( 3, 0 )->addWidget ( new Wt::WText ( "Normal price" ) );
        pTable->elementAt ( 3, 1 )->addWidget ( new Wt::WText ( offr._normal_price ) );

        pTable->elementAt ( 4, 0 )->addWidget ( new Wt::WText ( "Hyperlink" ) );
        pTable->elementAt ( 4, 1 )->addWidget ( new Wt::WText ( offr._hyperlink ) );

        this->addWidget ( pTable );
    }
    else if ( strPayload == "options" )
    {
        CWTable * pTable = new CWTable();
        pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Options" ) );

        pTable->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Airline" ) );
        pTable->elementAt ( 1, 1 )->addWidget ( new Wt::WText ( offr._airline ) );

        pTable->elementAt ( 2, 0 )->addWidget ( new Wt::WText ( "Flight direction" ) );
        pTable->elementAt ( 2, 1 )->addWidget ( new Wt::WText ( offr._direction ) );

        pTable->elementAt ( 3, 0 )->addWidget ( new Wt::WText ( "Luggage type" ) );
        pTable->elementAt ( 3, 1 )->addWidget ( new Wt::WText ( offr._luggage ) );

        pTable->elementAt ( 4, 0 )->addWidget ( new Wt::WText ( "Payload" ) );
        pTable->elementAt ( 4, 1 )->addWidget ( new Wt::WText ( offr._payload ) );

        this->addWidget ( pTable );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "Offer detail isn't found" ) );
    }
}

CWOfferDetailView::CWOfferDetailView ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    CWTable * pTable = new CWTable();

    pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Departure details" ) );

    Wt::WTableCell * pCell = nullptr;
    pCell = pTable->elementAt ( 1, 0 );
    CWLineEditField * pContD = new CWLineEditField ( "Continent", pCell );
    pCell->addWidget ( pContD );

    pCell = pTable->elementAt ( 2, 0 );
    CWLineEditField * pCityD = new CWLineEditField ( "City", pCell );
    pCell->addWidget ( pCityD );

    pCell = pTable->elementAt ( 3, 0 );
    CWLineEditField * pAirpD = new CWLineEditField ( "Airport", pCell );
    pCell->addWidget ( pAirpD );

    pCell = pTable->elementAt ( 4, 0 );
    CWLineEditField * pDaD = new CWLineEditField ( "Date", pCell );
    pCell->addWidget ( pDaD );

    /** ### ####################################################################### */

    pTable->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( "Arrival details" ) );

    pCell = pTable->elementAt ( 1, 2 );
    CWLineEditField * pContA = new CWLineEditField ( "Continent", pCell );
    pCell->addWidget ( pContA );

    pCell = pTable->elementAt ( 2, 2 );
    CWLineEditField * pCityA = new CWLineEditField ( "City", pCell );
    pCell->addWidget ( pCityA );

    pCell = pTable->elementAt ( 3, 2 );
    CWLineEditField * pAirpA = new CWLineEditField ( "Airport", pCell );
    pCell->addWidget ( pAirpA );

    pCell = pTable->elementAt ( 4, 2 );
    CWLineEditField * pDaA = new CWLineEditField ( "Date", pCell );
    pCell->addWidget ( pDaA );

    /** ### ####################################################################### */

    pTable->elementAt ( 0, 4 )->addWidget ( new Wt::WText ( "Price details" ) );

    pCell = pTable->elementAt ( 1, 4 );
    CWLineEditField * pCurrCode = new CWLineEditField ( "Currency code", pCell );
    pCell->addWidget ( pCurrCode );

    pCell = pTable->elementAt ( 2, 4 );
    CWLineEditField * pPrice = new CWLineEditField ( "Price", pCell );
    pCell->addWidget ( pPrice );

    pCell = pTable->elementAt ( 3, 4 );
    CWLineEditField * pNPrice = new CWLineEditField ( "Normal price", pCell );
    pCell->addWidget ( pNPrice );

    pCell = pTable->elementAt ( 4, 4 );
    CWLineEditField * pHplink = new CWLineEditField ( "Hyperlink", pCell );
    pCell->addWidget ( pHplink );

    /** ### ####################################################################### */

    pTable->elementAt ( 0, 6 )->addWidget ( new Wt::WText ( "Options" ) );

    pCell = pTable->elementAt ( 1, 6 );
    CWLineEditField * pAirl = new CWLineEditField ( "Airline", pCell );
    pCell->addWidget ( pAirl );

    pCell = pTable->elementAt ( 2, 6 );
    CWLineEditField * pFdir = new CWLineEditField ( "Flight direction", pCell );
    pCell->addWidget ( pFdir );

    pCell = pTable->elementAt ( 3, 6 );
    CWLineEditField * pLugg = new CWLineEditField ( "Luggage type", pCell );
    pCell->addWidget ( pLugg );

    pCell = pTable->elementAt ( 4, 6 );
    CWLineEditField * pPayl = new CWLineEditField ( "Payload", pCell );
    pCell->addWidget ( pPayl );

    Wt::WPushButton * pAddBtn = new Wt::WPushButton ( "Add" );
    pAddBtn->clicked().connect ( std::bind ( [=]()
    {
        OffersData::SOffer offer;
        offer.set_departure ( pContD->Value(), pCityD->Value(), pAirpD->Value(), pDaD->Value() );
        offer.set_arrival ( pContA->Value(), pCityA->Value(), pAirpA->Value(), pDaA->Value() );
        offer.set_prices ( pCurrCode->Value(), pPrice->Value(), pNPrice->Value(), pHplink->Value() );
        offer.set_options ( pAirl->Value(), pFdir->Value(), pLugg->Value(), pPayl->Value() );

        OffersData ofrs ( strPayload );
        ofrs.load();
        ofrs.add ( offer );
        ofrs.save();

        gCWSignals.signal_create_center_column.emit ( usrhash, "no_payload" );

    } ) );

    pCell = pTable->elementAt ( 5, 0 );
    pCell->addWidget ( pAddBtn );

    this->addWidget ( pTable );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

