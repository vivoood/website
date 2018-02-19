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
                m_pContent->addWidget ( Factory::Create ( d.strChildWidget, d.strChildWidgetData, p->strHash ) );
            } ) );
        }

        m_pContent->addWidget ( Factory::Create ( p->vTabButtons[0].strChildWidget, p->vTabButtons[0].strChildWidgetData, p->strHash ) );

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

void CWTabs::FillFromSignal ( std::string strWidgetName, std::string strData, std::string strHash )
{
    m_pContent->clear();
    m_pContent->addWidget ( Factory::Create ( strWidgetName, strData, strHash ) );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

