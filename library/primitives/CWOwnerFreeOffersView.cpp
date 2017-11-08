#include "CWOwnerFreeOffersView.h"

#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WCheckBox>

#include "CWOwnerData.h"

CWOwnerFreeOffersView::CWOwnerFreeOffersView ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOwnerFreeOffers * p = dynamic_cast<WidgetData::SOwnerFreeOffers*> ( pD );
    if ( p != nullptr )
    {
        Wt::WTable * table = new Wt::WTable();
        table->setHeaderCount ( 1 );
        table->setWidth ( Wt::WLength ( "100%" ) );

        table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "#" ) );
        table->elementAt ( 0, 0 )->setContentAlignment ( Wt::AlignCenter );
        for ( unsigned int i = 0; i < p->v.size(); i++ )
        {
            table->elementAt ( 0, i + 1 )->addWidget ( new Wt::WText ( p->v[i].label ) );
            table->elementAt ( 0, i + 1 )->setContentAlignment ( Wt::AlignCenter );
        }
        table->elementAt ( 0, p->v.size() + 1 )->addWidget ( new Wt::WText ( "Delete" ) );
        table->elementAt ( 0, p->v.size() + 1 )->setContentAlignment ( Wt::AlignCenter );

        CWOwnerData owner;
        owner.LoadFreeOffers();

        int cnt = 0;
        for ( std::map<std::string, CWFreeOffersData>::iterator it = owner.mapFreeOffers.begin(); it != owner.mapFreeOffers.end(); ++it )
        {
            ++cnt;
            int i = cnt;

            table->elementAt ( i, 0 )->addWidget ( new Wt::WText ( Wt::WString ( "{1}" ).arg ( cnt ) ) );
            table->elementAt ( i, 0 )->setContentAlignment ( Wt::AlignCenter );

            table->elementAt ( i, 1 )->addWidget ( new Wt::WText ( it->second.strFrom ) );
            table->elementAt ( i, 1 )->setContentAlignment ( Wt::AlignCenter );

            table->elementAt ( i, 2 )->addWidget ( new Wt::WText ( it->second.strTo ) );
            table->elementAt ( i, 2 )->setContentAlignment ( Wt::AlignCenter );

            table->elementAt ( i, 3 )->addWidget ( new Wt::WText ( it->second.strPrice ) );
            table->elementAt ( i, 3 )->setContentAlignment ( Wt::AlignCenter );

            table->elementAt ( i, 4 )->addWidget ( new Wt::WText ( it->second.strInstead ) );
            table->elementAt ( i, 4 )->setContentAlignment ( Wt::AlignCenter );

            table->elementAt ( i, 5 )->addWidget ( new Wt::WText ( it->second.strAirline ) );
            table->elementAt ( i, 5 )->setContentAlignment ( Wt::AlignCenter );

            Wt::WCheckBox * ch1 = new Wt::WCheckBox();
            ch1->setEnabled ( false );
            table->elementAt ( i, 6 )->addWidget ( ch1 );
            table->elementAt ( i, 6 )->setContentAlignment ( Wt::AlignCenter );

            Wt::WCheckBox * ch2 = new Wt::WCheckBox();
            ch2->setEnabled ( false );
            table->elementAt ( i, 7 )->addWidget ( ch2 );
            table->elementAt ( i, 7 )->setContentAlignment ( Wt::AlignCenter );

            table->elementAt ( i, 8 )->addWidget ( new Wt::WText ( it->second.strHyperlink ) );
            table->elementAt ( i, 8 )->setContentAlignment ( Wt::AlignCenter );

            table->elementAt ( i, 9 )->addWidget ( new Wt::WCheckBox() );
            table->elementAt ( i, 9 )->setContentAlignment ( Wt::AlignCenter );
        }

        this->addWidget ( table );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWOwnerFreeOffersView can't get SOwnerFreeOffers from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
