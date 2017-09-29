#include "CWOffer.h"

#include <Wt/WCssDecorationStyle>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

#include "CWSignals.h"

CWOffer::CWOffer ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffer * p = dynamic_cast<WidgetData::SOffer*> ( pD );
    if ( p != nullptr )
    {
        this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/" + p->offerBig.strTo + ".jpg" ) );
        this->setStyleClass ( p->strStyle );

        this->addWidget ( new Wt::WText ( p->offerBig.strFrom ) );
        this->addWidget ( new Wt::WBreak () );
        this->addWidget ( new Wt::WText ( p->offerBig.strTo ) );
        this->addWidget ( new Wt::WBreak () );

        Wt::WPushButton * pBtn = new Wt::WPushButton ( p->offerBig.strPrice );
        pBtn->clicked().connect ( std::bind ( [=]()
        {
            gCWSignals.signaloffertotab.emit ( "CWOfferBig", &p->offerBig );
        } ) );

        pBtn->setStyleClass ( p->strBtnStyle );
        this->addWidget ( pBtn );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
