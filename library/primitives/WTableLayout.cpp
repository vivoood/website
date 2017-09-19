/*
 * Velislav Velkov
 */

#include "WTableLayout.h"

#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTemplate>

WTableLayout::WTableLayout ( Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WTemplate * templ = new Wt::WTemplate ( Wt::WString::tr ( "web-site-table-layout-template" ) );
    Wt::WTable *table = new Wt::WTable();
    table->setStyleClass("web-site-table-layout-style");
    table->setWidth ( Wt::WLength ( "100%" ) );

    Wt::WText * p1 = new Wt::WText ( "col1" );
    table->elementAt ( 0, 0 )->addWidget ( p1 );
    table->elementAt ( 0, 0 )->setWidth ( Wt::WLength ( "15%" ) );

    Wt::WText * p2 = new Wt::WText ( "col2" );
    table->elementAt ( 0, 1 )->addWidget ( p2 );
    table->elementAt ( 0, 1 )->addWidget ( new Wt::WText() );
    table->elementAt ( 0, 1 )->setWidth ( Wt::WLength ( "65%" ) );

    Wt::WText * p3 = new Wt::WText ( "col3" );
    table->elementAt ( 0, 2 )->addWidget ( p3 );
    table->elementAt ( 0, 2 )->setWidth ( Wt::WLength ( "20%" ) );

    templ->bindWidget ( "table-layout", table );
    this->addWidget ( table );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
