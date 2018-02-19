#include "EntryOne.h"

#include <Wt/WBreak>
#include <Wt/WText>

#include "Factory.h"
#include "CWTable.h"

namespace
{

void CreateEntry ( std::string strUserHash, Wt::WContainerWidget * p )
{
    p->addWidget ( Factory::Create ( "CWCenterColumn", strUserHash ) );
}

}

EntryOne::EntryOne ( Wt::WApplication * pApp )
{
    pApp->setTitle ( "Change Title" );
    pApp->messageResourceBundle().use ( pApp->appRoot() + "WebTemplates" );
    pApp->useStyleSheet ( "WebStyleLW.css" );

    Wt::WTableCell * pCell = nullptr;
    CWTable *table = new CWTable();

    pCell = table->elementAt ( 0, 0 );
    pCell->setWidth ( Wt::WLength ( "12%" ) );
    pCell->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/bluebgr.png" ) );

    pCell = table->elementAt ( 0, 1 );
    CreateEntry ( "Guest", pCell );
    pCell->setWidth ( Wt::WLength ( "76%" ) );

    pCell = table->elementAt ( 0, 2 );
    pCell->setWidth ( Wt::WLength ( "12%" ) );
    pCell->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/bluebgr.png" ) );

    this->addWidget ( table );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
