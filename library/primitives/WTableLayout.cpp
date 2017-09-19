/*
 * Velislav Velkov
 */

#include "WTableLayout.h"

#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTemplate>

#include "WTabs.h"
#include "Constants.h"
#include "Factory.h"

WTableLayout::WTableLayout ( Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WTable *table = new Wt::WTable();
    table->setStyleClass ( "table-layout" );
    table->setWidth ( Wt::WLength ( "100%" ) );

    for ( unsigned int i = 0; i < gConstants.vTable.size(); i++ )
    {
        for ( unsigned int j = 0; j < gConstants.vTable[i].size(); j++ )
        {
            std::cout << i << " | " << j << " = " << gConstants.vTable[i][j].strLenght << std::endl;
            table->elementAt ( i, j )->addWidget ( Factory::Create ( gConstants.vTable[i][j].strWidgetName ) );
            table->elementAt ( i, j )->setStyleClass ( gConstants.vTable[i][j].strStyle );
            table->elementAt ( i, j )->setWidth ( Wt::WLength ( gConstants.vTable[i][j].strLenght.c_str() ) );
        }
    }

    this->addWidget ( table );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
