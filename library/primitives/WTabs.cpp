#include "WTabs.h"

#include <Wt/WTemplate>
#include <Wt/WPushButton>
#include <Wt/WGroupBox>
#include <Wt/WText>

#include "Constants.h"

WTabs::WTabs ( Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WTemplate * templ = new Wt::WTemplate ( Wt::WString::tr ( "web-site-menu-template" ) );

    Wt::WGroupBox *groupBox = new Wt::WGroupBox ( gConstants.vTabs.front().strTabName );
    for ( unsigned int i = 0; i < gConstants.vTabs.front().vTabDescr.size(); i++ )
    {
        groupBox->addWidget ( new Wt::WText ( gConstants.vTabs.front().vTabDescr[i] ) );
    }

    templ->bindWidget ( "groupbox", groupBox );

    for ( unsigned int i = 0; i < gConstants.vTabs.size(); i++ )
    {
        Wt::WPushButton * pBtn = new Wt::WPushButton ( gConstants.vTabs[i].strTabName );
        pBtn->setStyleClass ( "web-site-menu-button-style" );
        templ->bindWidget ( gConstants.vTabs[i].strTabTemplateId, pBtn );

        pBtn->clicked().connect ( std::bind ( [=]()
        {
            groupBox->clear();
            groupBox->setTitle ( pBtn->text() );

            Constants::STabData d = gConstants.FindTabData ( pBtn->text().toUTF8() );
            for ( unsigned int i = 0; i < d.vTabDescr.size(); i++ )
            {
                groupBox->addWidget ( new Wt::WText ( d.vTabDescr[i] ) );
            }
        } ) );
    }

    this->addWidget ( templ );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

