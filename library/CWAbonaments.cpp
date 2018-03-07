#include "CWAbonaments.h"

#include <Wt/WText>
#include <Wt/WBreak>

CWAbonaments::CWAbonaments ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "Montly - 999$" ) );

    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "Annual - 99999$" ) );

    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "Other offers ???" ) );

    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
