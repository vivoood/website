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
            std::vector< std::vector< std::string > > v = u.ExportAbonaments ( u );

            Wt::WTable * table = new Wt::WTable();
            table->setHeaderCount ( 1 );
            table->setWidth ( Wt::WLength ( "100%" ) );

            for ( unsigned int i = 0; i < v.size(); ++i )
            {
                for ( unsigned int j = 0; j < v[i].size(); ++j )
                {
                    table->elementAt ( i, j )->addWidget ( new Wt::WText ( v[i][j] ) );
                    table->elementAt ( i, j )->setContentAlignment ( Wt::AlignLeft );
                }
            }

            for ( unsigned int i = 1; i < v.size(); ++i )
            {
                Wt::WPushButton * btn = new Wt::WPushButton ( "" );
                btn->setLink ( Wt::WLink ( "https://paypal.com/" ) );
                btn->setIcon ( Wt::WLink ( "pics/paypal.png" ) );
                if ( u._vAbon[i-1]._payd )
                {
                    btn->setEnabled ( false );
                    btn->decorationStyle().setBackgroundColor ( Wt::WColor ( Wt::gray ) );
                }
                table->elementAt ( i, v[i].size() )->addWidget ( btn );
                table->elementAt ( i, v[i].size() )->setContentAlignment ( Wt::AlignLeft );
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
