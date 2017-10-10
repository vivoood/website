#include "Factory.h"

#include <Wt/WContainerWidget>
#include <Wt/WText>

#include "CWFooter.h"
#include "CWHeader.h"
#include "CWOffer.h"
#include "CWPublicOffers.h"
#include "CWTableLayout.h"
#include "CWTabs.h"
#include "CWFAQ.h"
#include "CWContacts.h"
#include "CWOfferBig.h"
#include "CWLogin.h"
#include "CWLeftCol.h"
#include "CWAfterLogin.h"
#include "CWUserLineInput.h"
#include "CWRegisterAccount.h"
#include "CWCombo.h"
#include "CWAccount.h"
#include "CWRadioButtons.h"
#include "CWContiCtryForm.h"
#include "CWQuery.h"

#include "Constants.h"

Wt::WWidget* Factory::Create ( std::string strWidget, std::string strData, std::string strHash )
{
    IWidgetData * pD = gConstants.GetData ( strData, strHash );
    return Factory::Create ( strWidget, pD );
}

Wt::WWidget* Factory::Create ( std::string strWidget, IWidgetData * pD )
{
    if ( strWidget == "WContainerWidget" )
        return new Wt::WContainerWidget();

    if ( strWidget == "CWTabs" )
        return new CWTabs ( pD );

    if ( strWidget == "CWHeader" )
        return new CWHeader ( pD );

    if ( strWidget == "CWTableLayout" )
        return new CWTableLayout ( pD );

    if ( strWidget == "CWFooter" )
        return new CWFooter ( pD );

    if ( strWidget == "CWOffer" )
        return new CWOffer ( pD );

    if ( strWidget == "CWFAQ" )
        return new CWFAQ ( pD );

    if ( strWidget == "CWPublicOffers" )
        return new CWPublicOffers ( pD );

    if ( strWidget == "CWContacts" )
        return new CWContacts ( pD );

    if ( strWidget == "CWOfferBig" )
        return new CWOfferBig ( pD );

    if ( strWidget == "CWLogin" )
        return new CWLogin ( pD );

    if ( strWidget == "CWLeftCol" )
        return new CWLeftCol ( pD );

    if ( strWidget == "CWAfterLogin" )
        return new CWAfterLogin ( pD );

    if ( strWidget == "CWRegisterAccount" )
        return new CWRegisterAccount ( pD );

    if ( strWidget == "CWAccount" )
        return new CWAccount ( pD );

    if ( strWidget == "CWRadioButtons" )
        return new CWRadioButtons ( pD );

    if ( strWidget == "CWContiCtryForm" )
        return new CWContiCtryForm ( pD );

    if ( strWidget == "CWQuery" )
        return new CWQuery ( pD );

    return new Wt::WText ( "n/a" );
}

Wt::WWidget * Factory::CreateUserLineInput ( std::string value )
{
    std::stringstream ss;
    ss << value;
    return new CWUserLineInput ( gConstants.GetData ( "SUserLineInput" ), ss );
}

Wt::WWidget * Factory::CreateComboBox ( std::string data, const std::string & label, const std::vector<std::string> & values )
{
    return new CWCombo ( gConstants.GetData ( data ), label, values );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
