#include "CWTabs.h"

#include <Wt/WTemplate>
#include <Wt/WPushButton>
#include <Wt/WGroupBox>
#include <Wt/WText>
#include <Wt/WBreak>

#include "Factory.h"

CWTabs::CWTabs ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    m_pContent = new Wt::WContainerWidget();

    WidgetData::STabs * p = dynamic_cast<WidgetData::STabs*> ( pD );
    unsigned int nButtonsCount = p->vTabButtons.size();

    if ( p != nullptr )
    {
        for ( unsigned int i = 0; i < nButtonsCount; i++ )
        {
            WidgetData::STabButtonsData d = p->vTabButtons[i];

            Wt::WPushButton * pBtn = new Wt::WPushButton ( d.strTabName );
            pBtn->setStyleClass ( d.strTabButtonStyle );
            this->addWidget ( pBtn );

            pBtn->clicked().connect ( std::bind ( [=]()
            {
                m_pContent->clear();
                m_pContent->addWidget ( Factory::Create ( d.content.strChildWidget, &p->vTabButtons[i].content ) );
                m_pContent->setStyleClass ( d.strWidgetStyle );
            } ) );
        }

        this->addWidget ( new Wt::WBreak() );
        this->addWidget ( m_pContent );
        this->setStyleClass ( p->strTabStyle );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 




