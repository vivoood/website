/*
 * Velislav Velkov
 */

#include "CWTableLayout.h"

#include <Wt/WTable>
#include <Wt/WTableCell>
// #include <Wt/WLineEdit>
// #include <Wt/WText>
// #include <Wt/WTemplate>
// #include <Wt/WCssDecorationStyle>
// #include <Wt/WColor>

#include "Factory.h"

CWTableLayout::CWTableLayout ( TABLE tdat, std::string strHash, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WTable *table = new Wt::WTable();
    table->setStyleClass ( "table-layout" );
    table->setWidth ( Wt::WLength ( "100%" ) );

    for ( unsigned int i = 0; i < tdat.size(); i++ )
    {
        for ( unsigned int j = 0; j < tdat[i].size(); j++ )
        {
            Wt::WTableCell * pCell = table->elementAt ( i, j );
            pCell->addWidget ( Factory::Create ( tdat[i][j], strHash ) );
        }
    }

    this->addWidget ( table );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
