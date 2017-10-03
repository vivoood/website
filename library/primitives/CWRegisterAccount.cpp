#include "CWRegisterAccount.h"

#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WBreak>

#include "Factory.h"
#include "CWUserLineInput.h"
#include "CWValidators.h"

CWRegisterAccount::CWRegisterAccount ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    CWUserLineInput * username = dynamic_cast<CWUserLineInput*> ( Factory::CreateUserLineInput ( "Username" ) );
    if ( username != nullptr )
    {
        username->pEdit->setValidator ( new CWValidators::UsernameValidator() );
        this->addWidget ( username );
    }

    CWUserLineInput * email = dynamic_cast<CWUserLineInput*> ( Factory::CreateUserLineInput ( "E-mail_address" ) );
    if ( email != nullptr )
    {
        email->pEdit->setValidator ( new CWValidators::EmailValidator() );
        this->addWidget ( email );
    }

    CWUserLineInput * password = dynamic_cast<CWUserLineInput*> ( Factory::CreateUserLineInput ( "Password" ) );
    if ( password != nullptr )
    {
        password->pEdit->setEchoMode ( Wt::WLineEdit::Password );
        this->addWidget ( password );
    }

    CWUserLineInput * passwordconfirm = dynamic_cast<CWUserLineInput*> ( Factory::CreateUserLineInput ( "Confirm_password" ) );
    if ( passwordconfirm != nullptr )
    {
        passwordconfirm->pEdit->setEchoMode ( Wt::WLineEdit::Password );
        this->addWidget ( passwordconfirm );
    }

    std::string label ( "Gender" );
    std::vector< std::string > values = { "Male", "Female", "Other" };
    this->addWidget ( Factory::CreateComboBox ( label, values ) );

    this->addWidget ( Factory::CreateUserLineInput ( "Country" ) );
    this->addWidget ( Factory::CreateUserLineInput ( "I'am_not_robot" ) );

    Wt::WPushButton * pBtn = new Wt::WPushButton ( "Continue" );
    pBtn->setStyleClass ( "menu-buttons" );
    pBtn->clicked().connect ( std::bind ( [=]()
    {
        this->addWidget ( new Wt::WBreak() );

        std::vector< std::string > v;
        v.push_back ( CWRegisterAccount::Validate ( this, username->pEdit, "username" ) );
        v.push_back ( CWRegisterAccount::Validate ( this, email->pEdit, "e-mail address" ) );
        v.push_back ( CWRegisterAccount::Validate ( this, password->pEdit, "password" ) );
        v.push_back ( CWRegisterAccount::Validate ( this, passwordconfirm->pEdit, "password confirm" ) );

        Wt::WContainerWidget * contError = new Wt::WContainerWidget();
        for ( auto it : v )
        {
            contError->addWidget ( new Wt::WBreak() );
            contError->addWidget ( new Wt::WText ( it ) );
        }
        contError->setStyleClass ( "menu-buttons-bgr" );
        this->addWidget ( contError );

    } ) );
    this->addWidget ( pBtn );
}

std::string CWRegisterAccount::Validate ( Wt::WContainerWidget * pThis, Wt::WLineEdit* p, std::string name )
{
    Wt::WValidator::State st = p->validate();
    if ( st == Wt::WValidator::InvalidEmpty )
        name.append ( " is empty" );
    else if ( st == Wt::WValidator::Invalid )
        name.append ( " is not valid" );
    else if ( st == Wt::WValidator::Valid )
        return "";
    return name;
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
