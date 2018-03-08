#include "CWIntroPage.h"

#include <Wt/WText>
#include <Wt/WBreak>

#include "CWTable.h"
#include "Factory.h"

CWIntroPage::CWIntroPage ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( Factory::Create ( "CWLoginCell", "no_payload", usrhash, this ) );
    this->addWidget ( Factory::Create ( "CWChooseContinent", "no_payload", usrhash, this ) );
    this->addWidget ( Factory::Create ( "CWPublicOffersView", strPayload, usrhash, this ) );
    this->addWidget ( Factory::Create ( "CWHowItWorks", "no_payload", usrhash, this ) );
    this->addWidget ( Factory::Create ( "CWFaq", "no_payload", usrhash, this ) );
    if ( usrhash != "Guest" )
    {
        this->addWidget ( Factory::Create ( "CWAbonaments", "no_payload", usrhash, this ) );
    }
    this->addWidget ( Factory::Create ( "CWPublicOffersView", "show_best_offers", usrhash, this ) );

    CWTable * pTableTasks = new CWTable();
    pTableTasks->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    pTableTasks->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Additional Tasks" ) );
    pTableTasks->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    pTableTasks->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );

    pTableTasks->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Add description for each abonament" ) );
    pTableTasks->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Show abonament page if needed and if valid user hash" ) );
    pTableTasks->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Remaining time of abonament" ) );
    pTableTasks->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Send mail" ) );
    pTableTasks->elementAt ( 2, 0 )->addWidget ( new Wt::WText ( "Create abonaments" ) );
    pTableTasks->elementAt ( 3, 0 )->addWidget ( new Wt::WText ( "Validation of all input fields" ) );
    pTableTasks->elementAt ( 4, 0 )->addWidget ( new Wt::WText ( "Remove WT signals" ) );
    pTableTasks->elementAt ( 5, 0 )->addWidget ( new Wt::WText ( "Check all static functions" ) );
    pTableTasks->elementAt ( 6, 0 )->addWidget ( new Wt::WText ( "Referance vs copy" ) );
    pTableTasks->elementAt ( 7, 0 )->addWidget ( new Wt::WText ( "Smart pointers" ) );
    pTableTasks->elementAt ( 8, 0 )->addWidget ( new Wt::WText ( "Add system info for sessions" ) );
    this->addWidget ( pTableTasks );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


