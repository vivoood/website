#include "CWOffer.h"

#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

CWOffer::CWOffer ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffer * p = dynamic_cast<WidgetData::SOffer*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyle );

        Wt::WText* pTxt = new Wt::WText ( p->strDirection );
        this->addWidget ( pTxt );

        this->addWidget ( new Wt::WBreak () );

        Wt::WPushButton * pBtn = new Wt::WPushButton ( p->strPrice );
        pBtn->setStyleClass ( "default-offer-button" );
        this->addWidget ( pBtn );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
