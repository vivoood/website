#include "CWTable.h"

#include <stdlib.h> 
#include <Wt/WCssDecorationStyle>

CWTable::CWTable ( Wt::WContainerWidget* parent ) : Wt::WTable ( parent )
{
    this->decorationStyle().setBackgroundColor ( Wt::WColor ( rand() % 255, rand() % 255, rand() % 255, rand() % 255 ) );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
