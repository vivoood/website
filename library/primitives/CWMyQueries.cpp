#include "CWMyQueries.h"

#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "CWUser.h"

CWMyQueries::CWMyQueries ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::STabButtonsContentData * p = dynamic_cast<WidgetData::STabButtonsContentData*> ( pD );
    if ( p != nullptr )
    {
        CWUser u;
        if ( u.load ( pD->strHash ) )
        {
            Wt::WTable * table = new Wt::WTable();
            table->setHeaderCount ( 1 );
            table->setWidth ( Wt::WLength ( "100%" ) );

            table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "#" ) );
            table->elementAt ( 0, 1 )->addWidget ( new Wt::WText ( "First Name" ) );
            table->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( "Last Name" ) );
            table->elementAt ( 0, 3 )->addWidget ( new Wt::WText ( "Pay" ) );

            const std::vector<CWUser::SAbon> & v = u._vAbon;

            std::vector<std::string> abonam = { "2.99$", "4.99$", "9.99$" };

            for ( unsigned int i = 0; i < v.size(); ++i )
            {
                const CWUser::SAbon & ab = v[i];
                int row = i + 1;

                table->elementAt ( row, 0 )->addWidget ( new Wt::WText ( Wt::WString ( "{1}" ) .arg ( row ) ) );
                table->elementAt ( row, 1 )->addWidget ( new Wt::WText ( abonam[ab._abon % abonam.size()] ) );
                table->elementAt ( row, 2 )->addWidget ( new Wt::WText ( ab._from._conti + " / " + ab._from._ctry + " / " + ab._from._city ) );
                table->elementAt ( row, 3 )->addWidget ( new Wt::WText ( ab._to._conti + " / " + ab._to._ctry + " / " + ab._to._city ) );
                table->elementAt ( row, 4 )->addWidget ( new Wt::WText ( ab._date ) );
                table->elementAt ( row, 5 )->addWidget ( new Wt::WText ( ab._adults ) );
                table->elementAt ( row, 6 )->addWidget ( new Wt::WText ( ab._budget ) );

                Wt::WPushButton * btn = new Wt::WPushButton ( ( ab._payd ? "paid" : "pay" ) );
                table->elementAt ( row, 7 )->addWidget ( btn );
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
        this->addWidget ( new Wt::WText ( "Can't get STabButtonsContentData from IWidgetData " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
