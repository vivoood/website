#include "CWCenterColumn.h"

#include <Wt/WText>
#include <Wt/WBreak>

#include "CWTable.h"
#include "Factory.h"
#include "CWUser.h"

CWCenterColumn::CWCenterColumn ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
//     if ( usrhash == "SignIn" )
//     {
//         this->addWidget ( Factory::Create ( "CWSignIn", "no_payload", usrhash ) );
//     }
//     else if ( CWUser::CheckOwner ( usrhash ) )
//     {
        this->addWidget ( Factory::Create ( "CWOwnerPage", "no_payload", usrhash ) );
//     }
//     else
//     {
//         this->addWidget ( Factory::Create ( "CWIntroPage", "no_payload", usrhash ) );
//     }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

