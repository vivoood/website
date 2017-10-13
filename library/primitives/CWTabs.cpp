#include "CWTabs.h"

#include <Wt/WTemplate>
#include <Wt/WPushButton>
#include <Wt/WGroupBox>
#include <Wt/WText>
#include <Wt/WBreak>

#include "Factory.h"
#include "CWSignals.h"

CWTabs::CWTabs ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WContainerWidget * pButtonsContainer = new Wt::WContainerWidget();
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
            pButtonsContainer->addWidget ( pBtn );

            pBtn->clicked().connect ( std::bind ( [=]()
            {
                m_pContent->clear();
                if ( p->vTabButtons[i].content.strChildData == "n/a" )
                {
                    m_pContent->addWidget ( Factory::Create ( d.content.strChildWidget, &p->vTabButtons[i].content ) );
                }
                else
                {
                    m_pContent->addWidget ( Factory::Create ( d.content.strChildWidget, p->vTabButtons[i].content.strChildData, p->strHash ) );
                }

            } ) );
        }

        m_pContent->addWidget ( Factory::Create ( p->vTabButtons[0].content.strChildWidget, &p->vTabButtons[0].content ) );

        pButtonsContainer->setStyleClass ( p->strTabStyle );
        this->addWidget ( pButtonsContainer );
        this->addWidget ( new Wt::WBreak() );
        this->addWidget ( m_pContent );

        gCWSignals.signaloffertotab.connect ( this, &CWTabs::FillFromSignal );
        gCWSignals.signallogintotabs.connect ( this, &CWTabs::FillFromSignal );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWTabs can't get STabs from IWidgetData for user: " + pD->strHash ) );
    }
}

void CWTabs::FillFromSignal ( std::string strWidgetName, IWidgetData * pD )
{
    m_pContent->clear();
    m_pContent->addWidget ( Factory::Create ( strWidgetName, pD ) );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
