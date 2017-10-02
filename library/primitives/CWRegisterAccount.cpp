#include "CWRegisterAccount.h"

#include "Factory.h"

CWRegisterAccount::CWRegisterAccount ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    this->addWidget ( Factory::CreateUserLineInput ( "Username" ) );
    this->addWidget ( Factory::CreateUserLineInput ( "E-mail_address" ) );
    this->addWidget ( Factory::CreateUserLineInput ( "Password" ) );
    this->addWidget ( Factory::CreateUserLineInput ( "Confirm_password" ) );
    this->addWidget ( Factory::CreateUserLineInput ( "Gender" ) );
    this->addWidget ( Factory::CreateUserLineInput ( "Country" ) );
    this->addWidget ( Factory::CreateUserLineInput ( "I'am_not_robot" ) );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
