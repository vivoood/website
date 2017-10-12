#include "CWAfterLogin.h"

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

#include "CWSignals.h"
#include "CWUser.h"

CWAfterLogin::CWAfterLogin ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SLogin * p = dynamic_cast<WidgetData::SLogin*> ( pD );
    if ( p != nullptr )
    {
        this->addWidget ( new Wt::WBreak() );

        CWUser u;
        u.load ( p->strHash );

        Wt::WText * pUserLabel = new Wt::WText ( "Welcome " + u._user );
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
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
