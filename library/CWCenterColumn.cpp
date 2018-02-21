#include "CWCenterColumn.h"

#include <Wt/WText>
#include <Wt/WBreak>

#include "CWTable.h"
#include "Factory.h"
#include "CWUser.h"

CWCenterColumn::CWCenterColumn ( std::string usrhash, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
//     if ( usrhash == "SignIn" )
//     {
//         this->addWidget ( Factory::Create ( "CWSignIn", usrhash ) );
//     }
//     else if ( CWUser::CheckOwner ( usrhash ) )
//     {
        this->addWidget ( Factory::Create ( "CWOwnerPage", usrhash ) );
//     }
//     else
//     {
//         this->addWidget ( Factory::Create ( "CWIntroPage", usrhash ) );
//     }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

