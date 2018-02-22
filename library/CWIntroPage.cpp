#include "CWIntroPage.h"

#include <Wt/WText>
#include <Wt/WBreak>

#include "CWTable.h"
#include "Factory.h"

CWIntroPage::CWIntroPage ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    /** ### Login */
    CWTable * pTable = new CWTable();
    pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "empty" ) );
    pTable->elementAt ( 0, 3 )->addWidget ( new Wt::WText ( "logo" ) );
    pTable->elementAt ( 0, 5 )->addWidget ( Factory::Create ( "CWLoginCell", "no_payload", usrhash, pTable->elementAt ( 0, 5 ) ) );
    this->addWidget ( pTable );

    CWTable * pTableContinentLocation = new CWTable();
    pTableContinentLocation->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "empty" ) );

    pTableContinentLocation->elementAt ( 0, 4 )->addWidget ( new Wt::WBreak() );
    pTableContinentLocation->elementAt ( 0, 4 )->addWidget ( new Wt::WBreak() );
    pTableContinentLocation->elementAt ( 0, 4 )->addWidget ( new Wt::WBreak() );
    pTableContinentLocation->elementAt ( 0, 4 )->addWidget ( new Wt::WText ( "Choose your continent location to see cheap flights" ) );
    pTableContinentLocation->elementAt ( 0, 4 )->addWidget ( new Wt::WBreak() );
    pTableContinentLocation->elementAt ( 0, 4 )->addWidget ( new Wt::WBreak() );
    pTableContinentLocation->elementAt ( 0, 4 )->addWidget ( new Wt::WBreak() );
    pTableContinentLocation->elementAt ( 0, 4 )->addWidget ( new Wt::WBreak() );

    pTableContinentLocation->elementAt ( 0, 8 )->addWidget ( new Wt::WText ( "empty" ) );
    this->addWidget ( pTableContinentLocation );

    /** ### Random free offers */
    this->addWidget ( Factory::Create ( "CWPublicOffersView", "show_free_offers_random", usrhash, this ) );

    CWTable * pTableHowItWork = new CWTable();
    for ( int i = 0; i < 5; i++ )
        pTableHowItWork->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    pTableHowItWork->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "How it works" ) );
    for ( int i = 0; i < 5; i++ )
        pTableHowItWork->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    this->addWidget ( pTableHowItWork );

    CWTable * pTableFAQ = new CWTable();
    for ( int i = 0; i < 5; i++ )
        pTableFAQ->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    pTableFAQ->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "FAQ page" ) );
    for ( int i = 0; i < 5; i++ )
        pTableFAQ->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    this->addWidget ( pTableFAQ );

    CWTable * pTablePrices = new CWTable();
    for ( int i = 0; i < 5; i++ )
        pTablePrices->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    pTablePrices->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Prices abonaments ......." ) );
    for ( int i = 0; i < 5; i++ )
        pTablePrices->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    this->addWidget ( pTablePrices );

    /** ### Top 5 best offers */
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


