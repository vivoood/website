#include "CWLogin.h"

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>
#include <Wt/WCssDecorationStyle>

#include "CWSignals.h"
#include "CWHash.h"
#include "CWUser.h"

CWLogin::CWLogin ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SLogin * p = dynamic_cast<WidgetData::SLogin*> ( pD );
    if ( p != nullptr )
    {
        this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/login_bgr.png" ), Wt::WCssDecorationStyle::NoRepeat, Wt::CenterX );

        this->addWidget ( new Wt::WBreak() );

        Wt::WFont f ( Wt::WFont::SansSerif );
        f.setSize ( "20" );
        f.setWeight ( Wt::WFont::Bold );

        Wt::WText * pUserLabel = new Wt::WText ( "_e-mail__" );
        pUserLabel->decorationStyle().setFont ( f );
        pUserLabel->setStyleClass ( p->strStyleFields );
        this->addWidget ( pUserLabel );

        Wt::WLineEdit * pUserEdit = new Wt::WLineEdit();
        pUserEdit->setStyleClass ( p->strStyleFields );
        this->addWidget ( pUserEdit );

        this->addWidget ( new Wt::WBreak() );

        Wt::WText * pPassLabel = new Wt::WText ( "__pass__" );
        pPassLabel->decorationStyle().setFont ( f );
        pPassLabel->setStyleClass ( p->strStyleFields );
        this->addWidget ( pPassLabel );

        Wt::WLineEdit * pPassEdit = new Wt::WLineEdit();
        pPassEdit->setEchoMode ( Wt::WLineEdit::Password );
        pPassEdit->setStyleClass ( p->strStyleFields );
        this->addWidget ( pPassEdit );

        this->addWidget ( new Wt::WBreak() );

        Wt::WPushButton * pLoginBtn = new Wt::WPushButton ( "Login" );
        pLoginBtn->setStyleClass ( p->strStyleBtns );
        pLoginBtn->clicked().connect ( std::bind ( [=]()
        {
            std::string strHash ( CWHash::Get ( pUserEdit->text().toUTF8() ) );
            CWUser u;
            if ( u.load ( strHash ) )
            {
                if ( u._pass == pPassEdit->text().toUTF8() )
                {
                    gCWSignals.signallogintomainwidget.emit ( strHash );
                }
                else
                {
                    this->addWidget ( new Wt::WBreak() );
                    this->addWidget ( new Wt::WText ( "Invalid user or Password" ) );
                }
            }
            else
            {
                this->addWidget ( new Wt::WBreak() );
                this->addWidget ( new Wt::WText ( "Invalid User or password" ) );
            }

        } ) );
        this->addWidget ( pLoginBtn );

        Wt::WPushButton * pRegBtn = new Wt::WPushButton ( "Register" );
        pRegBtn->setStyleClass ( p->strStyleBtns );
        pRegBtn->clicked().connect ( std::bind ( [=]()
        {
            gCWSignals.signallogintotabs.emit ( "CWRegisterAccount", "SRegister", p->strHash );
        } ) );
        this->addWidget ( pRegBtn );

        this->setStyleClass ( p->strStyleCommon );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWLogin can't get SLogin from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
