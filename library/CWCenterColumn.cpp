#include "CWCenterColumn.h"

#include <Wt/WText>

#include "CWTable.h"

CWCenterColumn::CWCenterColumn ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    CWTable * pTable = new CWTable();
    
    pTable->elementAt ( 0, 0 )->addWidget( new Wt::WText("[0]") );
    this->addWidget(pTable);
}

