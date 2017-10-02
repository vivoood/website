#include "CWRegisterAccount.h"

#include <Wt/WLineEdit>

#include "Factory.h"
#include "CWUserLineInput.h"

CWRegisterAccount::CWRegisterAccount ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    this->addWidget ( Factory::CreateUserLineInput ( "Username" ) );
    this->addWidget ( Factory::CreateUserLineInput ( "E-mail_address" ) );

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
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

