#include "CWCenterColumn.h"

#include <Wt/WText>
#include <Wt/WBreak>

#include "CWTable.h"
#include "Factory.h"

CWCenterColumn::CWCenterColumn ( std::string usrhash, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    if ( usrhash == "SignIn" )
    {
        this->addWidget ( Factory::Create ( "CWSignIn", usrhash ) );
    }
    else
    {
        this->addWidget ( Factory::Create ( "CWIntroPage", usrhash ) );
//         this->addWidget ( new Wt::WText ( "Unknown hash " + usrhash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

