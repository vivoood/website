#include "CWIntroPage.h"

#include <Wt/WText>
#include <Wt/WBreak>

#include "CWTable.h"
#include "Factory.h"

CWIntroPage::CWIntroPage ( std::string usrhash, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    CWTable * pTable = new CWTable();
    pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "empty" ) );
    pTable->elementAt ( 0, 3 )->addWidget ( new Wt::WText ( "logo" ) );
    pTable->elementAt ( 0, 5 )->addWidget ( Factory::Create ( "CWLoginCell", usrhash, pTable->elementAt ( 0, 5 ) ) );
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

    CWTable * pTableFreeOffers = new CWTable();
    for ( int i = 0; i < 8; ++i )
    {
        for ( int j = 0; j < 5; j++ )
            pTableFreeOffers->elementAt ( i, 0 )->addWidget ( new Wt::WBreak() );

        std::stringstream ss;
        ss << "offer - " << i + 1;
        pTableFreeOffers->elementAt ( i, 0 )->addWidget ( new Wt::WText ( ss.str() ) );
    }
    this->addWidget ( pTableFreeOffers );

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

    CWTable * pTableBestDeals = new CWTable();

    for ( int i = 0; i < 2; i++ )
        pTableBestDeals->elementAt ( 0, 0 )->addWidget ( new Wt::WBreak() );
    pTableBestDeals->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Top 5 best deals 1)......." ) );

    for ( int i = 0; i < 2; i++ )
        pTableBestDeals->elementAt ( 1, 0 )->addWidget ( new Wt::WBreak() );
    pTableBestDeals->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Top 5 best deals 2)......." ) );

    for ( int i = 0; i < 2; i++ )
        pTableBestDeals->elementAt ( 2, 0 )->addWidget ( new Wt::WBreak() );
    pTableBestDeals->elementAt ( 2, 0 )->addWidget ( new Wt::WText ( "Top 5 best deals 3)......." ) );

    for ( int i = 0; i < 2; i++ )
        pTableBestDeals->elementAt ( 3, 0 )->addWidget ( new Wt::WBreak() );
    pTableBestDeals->elementAt ( 3, 0 )->addWidget ( new Wt::WText ( "Top 5 best deals 4)......." ) );

    for ( int i = 0; i < 2; i++ )
        pTableBestDeals->elementAt ( 4, 0 )->addWidget ( new Wt::WBreak() );
    pTableBestDeals->elementAt ( 4, 0 )->addWidget ( new Wt::WText ( "Top 5 best deals 5)......." ) );

    this->addWidget ( pTableBestDeals );


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
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
