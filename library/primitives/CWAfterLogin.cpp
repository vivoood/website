#include "CWAfterLogin.h"

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>
#include <Wt/WCssDecorationStyle>

#include "CWSignals.h"
#include "CWUser.h"

CWAfterLogin::CWAfterLogin ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SLogin * p = dynamic_cast<WidgetData::SLogin*> ( pD );
    if ( p != nullptr )
    {
        this->addWidget ( new Wt::WBreak() );

        this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/login_bgr.png" ), Wt::WCssDecorationStyle::NoRepeat, Wt::CenterX );

        Wt::WFont f ( Wt::WFont::SansSerif );
        f.setSize ( "20" );
        f.setWeight ( Wt::WFont::Bold );

        CWUser u;
        u.load ( p->strHash );

        Wt::WText * pUserLabel = new Wt::WText ( "Welcome " + u._user );
        pUserLabel->decorationStyle().setFont ( f );
        pUserLabel->setStyleClass ( p->strStyleFields );
        this->addWidget ( pUserLabel );

        this->addWidget ( new Wt::WBreak() );

        Wt::WText * pPassLabel = new Wt::WText ( "" );
        pPassLabel->setStyleClass ( p->strStyleFields );
        this->addWidget ( pPassLabel );

        this->addWidget ( new Wt::WBreak() );

        Wt::WPushButton * pLogoutBtn = new Wt::WPushButton ( "Logout" );
        pLogoutBtn->setStyleClass ( p->strStyleBtns );
        pLogoutBtn->clicked().connect ( std::bind ( [=]()
        {
            gCWSignals.signalafterlogintomainwidget.emit();
        } ) );
        this->addWidget ( pLogoutBtn );

        this->setStyleClass ( p->strStyleCommon );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWAfterLogin can't get SLogin from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
