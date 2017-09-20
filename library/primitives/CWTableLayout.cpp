/*
 * Velislav Velkov
 */

#include "CWTableLayout.h"

#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTemplate>

#include "Factory.h"

CWTableLayout::CWTableLayout ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::STable * pTable = dynamic_cast<WidgetData::STable*> ( pD );
    if ( pTable != nullptr )
    {
        Wt::WTable *table = new Wt::WTable();
        table->setStyleClass ( "table-layout" );
        table->setWidth ( Wt::WLength ( "100%" ) );

        for ( unsigned int i = 0; i < pTable->vTable.size(); i++ )
        {
            for ( unsigned int j = 0; j < pTable->vTable[i].size(); j++ )
            {
                std::cout << i << " | " << j << " = " << pTable->vTable[i][j].strLenght << std::endl;
                table->elementAt ( i, j )->addWidget ( Factory::Create ( pTable->vTable[i][j].strWidgetName ) );
                table->elementAt ( i, j )->setStyleClass ( pTable->vTable[i][j].strStyle );
                table->elementAt ( i, j )->setWidth ( Wt::WLength ( pTable->vTable[i][j].strLenght.c_str() ) );
            }
        }

        this->addWidget ( table );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
