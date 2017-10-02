#include "CWRegisterAccount.h"

#include "Factory.h"

CWRegisterAccount::CWRegisterAccount ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    this->addWidget ( CreateField ( "Username" ) );
    this->addWidget ( CreateField ( "E-mail_address" ) );
    this->addWidget ( CreateField ( "Password" ) );
    this->addWidget ( CreateField ( "Confirm_password" ) );
    this->addWidget ( CreateField ( "Gender" ) );
    this->addWidget ( CreateField ( "Country" ) );
    this->addWidget ( CreateField ( "I'am_not_robot" ) );
    
}

Wt::WWidget * CWRegisterAccount::CreateField ( std::string str )
{
    std::stringstream ss;
    ss << str;
    return Factory::Create ( "CWUserLineInput", "SUserLineInput", ss );
}


// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
