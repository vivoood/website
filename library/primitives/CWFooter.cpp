#include "CWFooter.h"

#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WLink>
#include <Wt/WAnchor>

#include <sstream>

#include "Factory.h"

CWFooter::CWFooter ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SFooter * p = dynamic_cast<WidgetData::SFooter*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyle );
        this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/continents.png" ), Wt::WCssDecorationStyle::NoRepeat, Wt::CenterX );

        Wt::WAnchor * pAnchor = new Wt::WAnchor ( Wt::WLink ( "https://flightradar24.com" ), "Flight radar" );
        this->addWidget ( pAnchor );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWFooter can't get SFooter from IWidgetData for user: " + pD->strHash ) );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
