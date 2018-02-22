#include "CWSignIn.h"

#include <Wt/WText>
#include <Wt/WPushButton>

#include "CWSignals.h"
#include "CWTable.h"
#include "CWUser.h"
#include "CWLineEditField.h"

CWSignIn::CWSignIn ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    CWTable * pTable = new CWTable();

    pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "empty" ) );
    pTable->elementAt ( 0, 1 )->addWidget ( new Wt::WText ( "empty" ) );
    pTable->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( "empty" ) );

    int i = 0;

    for ( std::map<std::string, CWLineEditField*>::iterator it = vData.begin(); it != vData.end(); ++it )
    {
        it->second = new CWLineEditField ( it->first, pTable->elementAt ( i, 3 ) );
        pTable->elementAt ( i, 3 )->addWidget ( it->second );
        i++;
    }

    Wt::WPushButton * pBackBtn = new Wt::WPushButton ( "<-Back" );
    pBackBtn->clicked().connect ( std::bind ( [=]()
    {
        gCWSignals.signal_create_center_column.emit ( "Guest" );
    } ) );
    pTable->elementAt ( 5, 3 )->addWidget ( pBackBtn );

    Wt::WPushButton * pRegBtn = new Wt::WPushButton ( "Register" );
    pRegBtn->clicked().connect ( std::bind ( [=]()
    {
        CWUser u;
        FillData ( u );
        u.save();
        
        gCWSignals.signal_create_center_column.emit ( u.hash() );
    } ) );
    pTable->elementAt ( 5, 3 )->addWidget ( pRegBtn );

    pTable->elementAt ( 0, 4 )->addWidget ( new Wt::WText ( "empty" ) );
    pTable->elementAt ( 0, 5 )->addWidget ( new Wt::WText ( "empty" ) );
    pTable->elementAt ( 0, 6 )->addWidget ( new Wt::WText ( "empty" ) );

    this->addWidget ( pTable );
}

void CWSignIn::FillData ( CWUser & u )
{
    std::map<std::string, CWLineEditField*>::iterator it = vData.end();

    it = vData.find ( "e-mail" );
    if ( it != vData.end() )
        u._mail = it->second->Value();

    it = vData.find ( "Password" );
    if ( it != vData.end() )
        u._pass = it->second->Value();

    it = vData.find ( "Username" );
    if ( it != vData.end() )
        u._user = it->second->Value();

    it = vData.find ( "Country" );
    if ( it != vData.end() )
        u._country = it->second->Value();

    it = vData.find ( "Gender" );
    if ( it != vData.end() )
        u._gender = it->second->Value();
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


