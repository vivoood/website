#include "CWOffer.h"

#include <Wt/WCssDecorationStyle>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

CWOffer::CWOffer ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffer * p = dynamic_cast<WidgetData::SOffer*> ( pD );
    if ( p != nullptr )
    {
        this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/" + p->strTo + ".jpg" ) );
        this->setStyleClass ( p->strStyle );

        this->addWidget ( new Wt::WText ( p->strFrom ) );
        this->addWidget ( new Wt::WBreak () );
        this->addWidget ( new Wt::WText ( p->strTo ) );
        this->addWidget ( new Wt::WBreak () );
        
        Wt::WPushButton * pBtn = new Wt::WPushButton ( p->strPrice );
        pBtn->setStyleClass ( p->strBtnStyle );
        this->addWidget ( pBtn );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
