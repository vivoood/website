#include "CWHowItWorks.h"

#include <Wt/WText>
#include <Wt/WBreak>

CWHowItWorks::CWHowItWorks ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( new Wt::WText ( "CWHowItWorks" ) );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
