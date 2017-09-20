#include "WTabs.h"

#include <Wt/WTemplate>
#include <Wt/WPushButton>
#include <Wt/WGroupBox>
#include <Wt/WText>

WTabs::WTabs ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::STabs * pTabs = dynamic_cast<WidgetData::STabs*> ( pD );
    if ( pTabs != nullptr )
    {
        for ( unsigned int i = 0; i < pTabs->vTabButtons.size(); i++ )
        {
            Wt::WPushButton * pBtn = new Wt::WPushButton ( pTabs->vTabButtons[i].strTabName );
            pBtn->setStyleClass ( pTabs->vTabButtons[i].strTabButtonStyle );
            this->addWidget ( pBtn );
        }

        this->setStyleClass ( pTabs->strTabStyle );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 




