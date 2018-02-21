#include "CWFreeOffers.h"

#include <Wt/WText>
#include <Wt/WPushButton>

#include "CWUser.h"
#include "CWTable.h"
#include "CWLineEditField.h"
#include "CWSignals.h"

CWFreeOffers::CWFreeOffers ( std::string usrhash, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    CWTable * pTable = new CWTable();

    pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "empty" ) );
    pTable->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( "Add FREE offers" ) );
    pTable->elementAt ( 0, 4 )->addWidget ( new Wt::WText ( "empty" ) );

    CWLineEditField * pDep = new CWLineEditField ( "Departure", pTable->elementAt ( 1, 2 ) );
    pTable->elementAt ( 1, 2 )->addWidget ( pDep );

    CWLineEditField * pArriv = new CWLineEditField ( "Arrival", pTable->elementAt ( 2, 2 ) );
    pTable->elementAt ( 2, 2 )->addWidget ( pArriv );

    CWLineEditField * pChp = new CWLineEditField ( "Cheap price", pTable->elementAt ( 3, 2 ) );
    pTable->elementAt ( 3, 2 )->addWidget ( pChp );

    CWLineEditField * pNorp = new CWLineEditField ( "Normal price", pTable->elementAt ( 4, 2 ) );
    pTable->elementAt ( 4, 2 )->addWidget ( pNorp );

    Wt::WPushButton * pAddBtn = new Wt::WPushButton ( "Add" );
    pAddBtn->clicked().connect ( std::bind ( [=]()
    {
        FreeOffersData::SOffer offer = { pDep->Value(), pArriv->Value(), pChp->Value(), pNorp->Value() };
        FreeOffersData ofrs;
        ofrs.add ( offer );
        gCWSignals.signal_create_center_column.emit ( usrhash );

    } ) );

    pTable->elementAt ( 6, 2 )->addWidget ( pAddBtn );

    this->addWidget ( pTable );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
