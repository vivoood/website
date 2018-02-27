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
    this->addWidget ( Factory::Create ( "CWAbonaments", "no_payload", usrhash, this ) );
    this->addWidget ( Factory::Create ( "CWPublicOffersView", "show_best_offers", usrhash, this ) );

    CWTable * pTableSuccessStories = new CWTable();
    for ( int i = 0; i < 2; i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            std::stringstream ss;
            ss << "Success stories id[" << i + 1 << "][" << j + 1 << "]";
            pTableSuccessStories->elementAt ( i, j )->addWidget ( new Wt::WBreak() );
            pTableSuccessStories->elementAt ( i, j )->addWidget ( new Wt::WText ( ss.str() ) );
            pTableSuccessStories->elementAt ( i, j )->addWidget ( new Wt::WBreak() );
            pTableSuccessStories->elementAt ( i, j )->addWidget ( new Wt::WBreak() );
        }
    }
    this->addWidget ( pTableSuccessStories );


    CWTable * pTableTasks = new CWTable();
    pTableTasks->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    pTableTasks->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Additional Tasks" ) );
    pTableTasks->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    pTableTasks->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );

    pTableTasks->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Validation of all input fields" ) );
    pTableTasks->elementAt ( 2, 0 )->addWidget ( new Wt::WText ( "Remove WT signals" ) );
    pTableTasks->elementAt ( 3, 0 )->addWidget ( new Wt::WText ( "Check all static functions" ) );
    pTableTasks->elementAt ( 4, 0 )->addWidget ( new Wt::WText ( "Referance vs copy" ) );
    pTableTasks->elementAt ( 5, 0 )->addWidget ( new Wt::WText ( "Smart pointers" ) );
    pTableTasks->elementAt ( 6, 0 )->addWidget ( new Wt::WText ( "Add system info for sessions" ) );
    this->addWidget ( pTableTasks );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


