#include "EntryOne.h"

#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WTableCell>

EntryOne::EntryOne ( Wt::WApplication * pApp )
{
    pApp->setTitle ( "Change Title" );

    pApp->messageResourceBundle().use ( pApp->appRoot() + "WebTemplates" );
    pApp->useStyleSheet ( "WebStyleLW.css" );

    Wt::WTable *table = new Wt::WTable();
    table->setWidth ( Wt::WLength ( "100%" ) );

    table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "col-1" ) );
    table->elementAt ( 0, 0 )->setWidth ( Wt::WLength ( "15%" ) );

    table->elementAt ( 0, 1 )->addWidget ( new Wt::WText ( "col-1" ) );
    table->elementAt ( 0, 1 )->setWidth ( Wt::WLength ( "70%" ) );

    table->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( "col-1" ) );
    table->elementAt ( 0, 2 )->setWidth ( Wt::WLength ( "15%" ) );

    this->addWidget ( table );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
