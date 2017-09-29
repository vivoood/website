#include "CWRegisterAccount.h"

#include "Factory.h"

CWRegisterAccount::CWRegisterAccount ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    std::string str("vvvvv");
    this->addWidget ( Factory::Create ( "CWUserLineInput", "SUserLineInput", &str ) );

//     WidgetData::X * p = dynamic_cast<WidgetData::X*> ( pD );
//     if ( p != nullptr )
//     {
//
//     }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
