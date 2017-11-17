#include "CWOwnerFreeOffersView.h"

#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WCheckBox>
#include <Wt/WPushButton>

#include "CWOwnerData.h"
#include "Factory.h"

namespace
{

std::string ConvertStr ( std::string str )
{
    std::replace ( str.begin(), str.end(), ':', ' ' );
    return str;
}

void Update ( Wt::WContainerWidget * root, WidgetData::SOwnerFreeOffers * p )
{
    root->clear();

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

    Wt::WPushButton * btnDelete = new Wt::WPushButton ( "Delete" );
    table->elementAt ( 0, p->v.size() + 1 )->addWidget ( btnDelete );
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

        table->elementAt ( i, 1 )->addWidget ( new Wt::WText ( ConvertStr ( it->second.strFrom ) ) );
        table->elementAt ( i, 1 )->setContentAlignment ( Wt::AlignCenter );

        table->elementAt ( i, 2 )->addWidget ( new Wt::WText ( ConvertStr ( it->second.strTo ) ) );
        table->elementAt ( i, 2 )->setContentAlignment ( Wt::AlignCenter );

        table->elementAt ( i, 3 )->addWidget ( new Wt::WText ( it->second.strPrice ) );
        table->elementAt ( i, 3 )->setContentAlignment ( Wt::AlignCenter );

        table->elementAt ( i, 4 )->addWidget ( new Wt::WText ( it->second.strInstead ) );
        table->elementAt ( i, 4 )->setContentAlignment ( Wt::AlignCenter );

        table->elementAt ( i, 5 )->addWidget ( new Wt::WText ( ConvertStr ( it->second.strAirline ) ) );
        table->elementAt ( i, 5 )->setContentAlignment ( Wt::AlignCenter );

        Wt::WCheckBox * ch1 = new Wt::WCheckBox();
        ch1->setEnabled ( false );
        ch1->setChecked ( it->second.bOneWay );
        table->elementAt ( i, 6 )->addWidget ( ch1 );
        table->elementAt ( i, 6 )->setContentAlignment ( Wt::AlignCenter );

        Wt::WCheckBox * ch2 = new Wt::WCheckBox();
        ch2->setEnabled ( false );
        ch2->setChecked ( it->second.bDirectFlight );
        table->elementAt ( i, 7 )->addWidget ( ch2 );
        table->elementAt ( i, 7 )->setContentAlignment ( Wt::AlignCenter );

        table->elementAt ( i, 8 )->addWidget ( new Wt::WText ( it->second.strHyperlink ) );
        table->elementAt ( i, 8 )->setContentAlignment ( Wt::AlignCenter );

        table->elementAt ( i, 9 )->addWidget ( new Wt::WCheckBox() );
        table->elementAt ( i, 9 )->setContentAlignment ( Wt::AlignCenter );
    }

    root->addWidget ( table );

    btnDelete->clicked().connect ( std::bind ( [=]()
    {
        std::vector<std::string> vHash;

        CWOwnerData ownerL;
        ownerL.LoadFreeOffers();

        int counter = 0;

        for ( std::map<std::string, CWFreeOffersData>::iterator it = ownerL.mapFreeOffers.begin(); it != ownerL.mapFreeOffers.end(); ++it )
        {
            ++counter;
            int id = counter;
            Wt::WTableCell * pCell = table->elementAt ( id, 9 );
            Wt::WWidget * w = pCell->widget ( 0 );
            Wt::WCheckBox * checkbox = dynamic_cast<Wt::WCheckBox *> ( w );

            if ( nullptr != checkbox )
            {
                bool checked = checkbox->isChecked();
                if ( checked )
                {
                    vHash.push_back ( ( *it ).first );
                }
            }
        }

        for ( auto & i : vHash )
        {
            ownerL.RemoveFreeOffer ( i );
        }
        ownerL.SaveFreeOffers();

        Update ( root, p );

    } ) );
}

}

CWOwnerFreeOffersView::CWOwnerFreeOffersView ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOwnerFreeOffers * p = dynamic_cast<WidgetData::SOwnerFreeOffers*> ( pD );
    if ( p != nullptr )
    {
        Update ( this, p );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWOwnerFreeOffersView can't get SOwnerFreeOffers from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
