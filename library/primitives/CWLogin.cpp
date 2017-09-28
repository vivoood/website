#include "CWLogin.h"

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

CWLogin::CWLogin ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WText * pUserLabel = new Wt::WText ( "Username" );
    pUserLabel->setStyleClass ( "login-fields-style" );
    this->addWidget ( pUserLabel );

    Wt::WLineEdit * pUserEdit = new Wt::WLineEdit();
    pUserEdit->setStyleClass ( "login-fields-style" );
    this->addWidget ( pUserEdit );

    this->addWidget ( new Wt::WBreak() );

    Wt::WText * pPassLabel = new Wt::WText ( "Password" );
    pPassLabel->setStyleClass ( "login-fields-style" );
    this->addWidget ( pPassLabel );

    Wt::WLineEdit * pPassEdit = new Wt::WLineEdit();
    pPassEdit->setStyleClass ( "login-fields-style" );
    this->addWidget ( pPassEdit );

    this->addWidget ( new Wt::WBreak() );

    Wt::WPushButton * pLoginBtn = new Wt::WPushButton ( "Login" );
    pLoginBtn->setStyleClass ( "login-button-style" );
    this->addWidget ( pLoginBtn );

    this->setStyleClass ( "login-style" );
//     this->setContentAlignment ( Wt::AlignmentFlag::AlignCenter );

//     WidgetData::X * p = dynamic_cast<WidgetData::X*> ( pD );
//     if ( p != nullptr )
//     {
//
//     }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
