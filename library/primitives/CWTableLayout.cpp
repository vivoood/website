/*
 * Velislav Velkov
 */

#include "CWTableLayout.h"

#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WTemplate>
#include <Wt/WCssDecorationStyle>
#include <Wt/WColor>

#include "Factory.h"

CWTableLayout::CWTableLayout ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::STable * p = dynamic_cast<WidgetData::STable*> ( pD );
    if ( p != nullptr )
    {
        Wt::WTable *table = new Wt::WTable();
        table->setStyleClass ( "table-layout" );
        table->setWidth ( Wt::WLength ( "100%" ) );

        for ( unsigned int i = 0; i < p->vTable.size(); i++ )
        {
            for ( unsigned int j = 0; j < p->vTable[i].size(); j++ )
            {
                Wt::WTableCell * pCell = table->elementAt ( i, j );
                WidgetData::STableData d = p->vTable[i][j];

                pCell->addWidget ( Factory::Create ( d.strWidgetName ) );
                pCell->setStyleClass ( d.strStyle );
                pCell->setWidth ( Wt::WLength ( d.strLenght.c_str() ) );

                if ( d.strBgrImg != "n/a" )
                {
                    pCell->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/" + d.strBgrImg + ".jpg" ) );
                }
            }
        }

        this->addWidget ( table );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
