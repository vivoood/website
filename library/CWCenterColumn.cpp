#include "CWCenterColumn.h"

#include <Wt/WText>
#include <Wt/WBreak>

#include "CWTable.h"

CWCenterColumn::CWCenterColumn ( std::string usrhash, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    CWTable * pTable = new CWTable();
    pTable->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "empty" ) );
    pTable->elementAt ( 0, 3 )->addWidget ( new Wt::WText ( "logo" ) );
    pTable->elementAt ( 0, 5 )->addWidget ( new Wt::WText ( usrhash ) );
    pTable->elementAt ( 1, 5 )->addWidget ( new Wt::WText ( "login" ) );
    this->addWidget ( pTable );

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

}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
