#include "WTabs.h"

#include <Wt/WTemplate>
#include <Wt/WPushButton>
#include <Wt/WGroupBox>
#include <Wt/WText>

#include "Constants.h"

WTabs::WTabs ( Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WTemplate * templ = new Wt::WTemplate ( Wt::WString::tr ( "web-site-menu-template" ) );

    for ( unsigned int i = 0; i < gConstants.vTabs.size(); i++ )
    {
        Wt::WPushButton * pBtn = new Wt::WPushButton ( gConstants.vTabs[i].first );
        pBtn->setStyleClass ( "web-site-menu-button-style" );
        templ->bindWidget ( gConstants.vTabs[i].second, pBtn );
    }

    Wt::WGroupBox *groupBox = new Wt::WGroupBox ( "A group box" );
    groupBox->addWidget ( new Wt::WText ( "<p>Some contents.</p>" ) );
    groupBox->addWidget ( new Wt::WText ( "<p>More contents.</p>" ) );
    templ->bindWidget ( "groupbox", groupBox );

    this->addWidget ( templ );
}


