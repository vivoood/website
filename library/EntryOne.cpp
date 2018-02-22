#include "EntryOne.h"

#include <Wt/WBreak>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>

#include "Factory.h"
#include "CWTable.h"
#include "CWSignals.h"

EntryOne::EntryOne ( Wt::WApplication * pApp )
{
    this->decorationStyle().setCursor ( Wt::PointingHandCursor );

    gCWSignals.signal_create_center_column.connect ( this, &EntryOne::CreateEntry );

    pApp->setTitle ( "Change Title" );
    pApp->messageResourceBundle().use ( pApp->appRoot() + "WebTemplates" );
    pApp->useStyleSheet ( "WebStyleLW.css" );

    CWTable *table = new CWTable();

    m_pCell = table->elementAt ( 0, 0 );
    m_pCell->setWidth ( Wt::WLength ( "12%" ) );
    m_pCell->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/bluebgr.png" ) );

    m_pCell = table->elementAt ( 0, 2 );
    m_pCell->setWidth ( Wt::WLength ( "12%" ) );
    m_pCell->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/bluebgr.png" ) );

    m_pCell = table->elementAt ( 0, 1 );
    gCWSignals.signal_create_center_column.emit ( "Guest" );
    m_pCell->setWidth ( Wt::WLength ( "76%" ) );

    this->addWidget ( table );
}

void EntryOne::CreateEntry ( std::string strUserHash )
{
    m_pCell->clear();
    m_pCell->addWidget ( Factory::Create ( "CWCenterColumn", "no_payload", strUserHash ) );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
