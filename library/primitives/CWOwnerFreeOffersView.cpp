#include "CWOwnerFreeOffersView.h"

#include <Wt/WTable>
#include <Wt/WText>

#include "CWOwnerData.h"

CWOwnerFreeOffersView::CWOwnerFreeOffersView ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    this->addWidget ( new Wt::WText ( "hdfgdsgdsf" ) );
    WidgetData::SOwnerFreeOffers * p = dynamic_cast<WidgetData::SOwnerFreeOffers*> ( pD );
    if ( p != nullptr )
    {
        Wt::WTable * table = new Wt::WTable();
        table->setHeaderCount ( 1 );
        table->setWidth ( Wt::WLength ( "100%" ) );

        table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "#" ) );
        table->elementAt ( 0, 0 )->setContentAlignment ( Wt::AlignLeft );
        for ( unsigned int i = 0; i < p->v.size(); i++ )
        {
            table->elementAt ( 0, i + 1 )->addWidget ( new Wt::WText ( p->v[i].label ) );
            table->elementAt ( 0, i + 1 )->setContentAlignment ( Wt::AlignLeft );
        }
        table->elementAt ( 0, p->v.size() + 1 )->addWidget ( new Wt::WText ( "Mark" ) );
        table->elementAt ( 0, p->v.size() + 1 )->setContentAlignment ( Wt::AlignLeft );

        CWOwnerData owner;
        owner.LoadFreeOffers();

        int cnt = 0;
        for ( std::map<std::string, CWFreeOffersData>::iterator it = owner.mapFreeOffers.begin(); it != owner.mapFreeOffers.end(); ++it )
        {
            ++cnt;
            it->second;
        }

        this->addWidget ( table );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWOwnerFreeOffersView can't get SOwnerFreeOffers from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
