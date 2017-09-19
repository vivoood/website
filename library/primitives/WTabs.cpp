#include "WTabs.h"

#include <Wt/WTemplate>
#include <Wt/WPushButton>
#include <Wt/WGroupBox>
#include <Wt/WText>

#include "Constants.h"

WTabs::WTabs ( Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    for ( unsigned int i = 0; i < gConstants.vMenuButtons.size(); i++ )
    {
        Wt::WPushButton * pBtn = new Wt::WPushButton ( gConstants.vMenuButtons[i].strTabName );
        pBtn->setStyleClass ( "menu-buttons" );
        this->addWidget ( pBtn );
    }
    
    this->setStyleClass("menu-buttons-bgr");
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

