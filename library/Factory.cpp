#include "Factory.h"

#include <Wt/WText>

#include "CWCenterColumn.h"
#include "CWLoginCell.h"
#include "CWIntroPage.h"
#include "CWSignIn.h"

Wt::WWidget * Factory::Create ( std::string strWidget, std::string strUserHash, Wt::WContainerWidget * parent )
{
    if ( strWidget == "CWCenterColumn" )
        return new CWCenterColumn ( strUserHash, parent );

    if ( strWidget == "CWLoginCell" )
        return new CWLoginCell ( strUserHash, parent );

    if ( strWidget == "CWIntroPage" )
        return new CWIntroPage ( strUserHash, parent );

    if ( strWidget == "CWSignIn" )
        return new CWSignIn ( strUserHash, parent );

    return new Wt::WText ( "Factory could not create " + strWidget );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

