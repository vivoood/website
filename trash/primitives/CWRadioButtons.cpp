#include "CWRadioButtons.h"

#include <Wt/WButtonGroup>
#include <Wt/WContainerWidget>
#include <Wt/WRadioButton>
#include <Wt/WTemplate>

CWRadioButtons::CWRadioButtons ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    p = dynamic_cast<WidgetData::SRadioButtons*> ( pD );
    if ( p != nullptr )
    {
        Wt::WContainerWidget * container = new Wt::WContainerWidget();
        container->setStyleClass ( p->strStyle );
        container->addWidget ( new Wt::WText ( "<h2>" + p->strMainMsg + "</h2>" ) );
        group = new Wt::WButtonGroup();

        for ( auto it : p->content )
        {
            Wt::WRadioButton * button = new Wt::WRadioButton ( it.first );
            container->addWidget ( button );
            group->addButton ( button );
        }

        int nDefaultId = 0;
        group->setSelectedButtonIndex ( nDefaultId );
        group->checkedChanged().connect ( this, &CWRadioButtons::Click );

        outMsg = new Wt::WText ( "<p>" + p->content[ nDefaultId ].second + "</p>" );
        container->addWidget ( outMsg );

        this->addWidget ( container );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWRadioButtons can't get SRadioButtons from IWidgetData for user: " + pD->strHash ) );
    }
}

void CWRadioButtons::Click ( Wt::WRadioButton* selection )
{
    Wt::WString text ( p->content[ group->id ( selection ) ].second );
    outMsg->setText ( Wt::WString ( "<p>" ) + text + "</p>" );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
