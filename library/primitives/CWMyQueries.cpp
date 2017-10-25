#include "CWMyQueries.h"

#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WPushButton>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>

#include "CWUser.h"

CWMyQueries::CWMyQueries ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SMyQuery * p = dynamic_cast<WidgetData::SMyQuery*> ( pD );
    if ( p != nullptr )
    {
        CWUser u;
        if ( u.load ( pD->strHash ) )
        {
            Wt::WTable * table = new Wt::WTable();
            table->setHeaderCount ( 1 );
            table->setWidth ( Wt::WLength ( "100%" ) );

            table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "#" ) );
            table->elementAt ( 0, 0 )->setContentAlignment ( Wt::AlignLeft );

            table->elementAt ( 0, 1 )->addWidget ( new Wt::WText ( "Price" ) );
            table->elementAt ( 0, 1 )->setContentAlignment ( Wt::AlignLeft );

            table->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( "From" ) );
            table->elementAt ( 0, 2 )->setContentAlignment ( Wt::AlignLeft );

            table->elementAt ( 0, 3 )->addWidget ( new Wt::WText ( "To" ) );
            table->elementAt ( 0, 3 )->setContentAlignment ( Wt::AlignLeft );

            table->elementAt ( 0, 4 )->addWidget ( new Wt::WText ( "Date" ) );
            table->elementAt ( 0, 4 )->setContentAlignment ( Wt::AlignLeft );

            table->elementAt ( 0, 5 )->addWidget ( new Wt::WText ( "Adult(s)" ) );
            table->elementAt ( 0, 5 )->setContentAlignment ( Wt::AlignLeft );

            table->elementAt ( 0, 6 )->addWidget ( new Wt::WText ( "Budget" ) );
            table->elementAt ( 0, 6 )->setContentAlignment ( Wt::AlignLeft );

            table->elementAt ( 0, 7 )->addWidget ( new Wt::WText ( "" ) );
            table->elementAt ( 0, 7 )->setContentAlignment ( Wt::AlignLeft );

            const std::vector<CWUser::SAbon> & v = u._vAbon;

            std::vector<std::string> abonam = { "2.99$", "4.99$", "9.99$" };

            for ( unsigned int i = 0; i < v.size(); ++i )
            {
                const CWUser::SAbon & ab = v[i];
                int row = i + 1;

                table->elementAt ( row, 0 )->addWidget ( new Wt::WText ( Wt::WString ( "{1}" ) .arg ( row ) ) );
                table->elementAt ( row, 0 )->setContentAlignment ( Wt::AlignLeft );

                table->elementAt ( row, 1 )->addWidget ( new Wt::WText ( abonam[ab._abon % abonam.size()] ) );
                table->elementAt ( row, 1 )->setContentAlignment ( Wt::AlignLeft );

                table->elementAt ( row, 2 )->addWidget ( new Wt::WText ( ab._from._conti + " / " + ab._from._ctry + " / " + ab._from._city ) );
                table->elementAt ( row, 2 )->setContentAlignment ( Wt::AlignLeft );

                table->elementAt ( row, 3 )->addWidget ( new Wt::WText ( ab._to._conti + " / " + ab._to._ctry + " / " + ab._to._city ) );
                table->elementAt ( row, 3 )->setContentAlignment ( Wt::AlignLeft );

                table->elementAt ( row, 4 )->addWidget ( new Wt::WText ( ab._date ) );
                table->elementAt ( row, 4 )->setContentAlignment ( Wt::AlignLeft );

                table->elementAt ( row, 5 )->addWidget ( new Wt::WText ( ab._adults ) );
                table->elementAt ( row, 5 )->setContentAlignment ( Wt::AlignLeft );

                table->elementAt ( row, 6 )->addWidget ( new Wt::WText ( ab._budget ) );
                table->elementAt ( row, 6 )->setContentAlignment ( Wt::AlignLeft );

                Wt::WPushButton * btn = new Wt::WPushButton ( "" );
                btn->setLink ( Wt::WLink ( "https://paypal.com/" ) );
                btn->setIcon ( Wt::WLink ( "pics/paypal.png" ) );
                if ( ab._payd )
                {
                    btn->setEnabled ( false );
                    btn->decorationStyle().setBackgroundColor ( Wt::WColor ( Wt::gray ) );
                }

                table->elementAt ( row, 7 )->addWidget ( btn );
                table->elementAt ( row, 7 )->setContentAlignment ( Wt::AlignLeft );
            }

            this->addWidget ( table );
        }
        else
        {
            this->addWidget ( new Wt::WText ( "Cant load user: " + pD->strHash ) );
        }
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWMyQueries can't get SMyQuery from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
