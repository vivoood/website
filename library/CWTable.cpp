#include "CWTable.h"

#include <stdlib.h> 
#include <Wt/WCssDecorationStyle>

CWTable::CWTable ( Wt::WContainerWidget* parent ) : Wt::WTable ( parent )
{
    this->setWidth ( Wt::WLength ( "100%" ) );
    this->decorationStyle().setBackgroundColor ( Wt::WColor ( 255 - rand() % 100, 255 - rand() % 100, 255 - rand() % 100, 255 - rand() % 100 ) );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
