#include "CWFaq.h"

#include <Wt/WText>
#include <Wt/WBreak>

CWFaq::CWFaq ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( new Wt::WText ( "CWFaq" ) );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
