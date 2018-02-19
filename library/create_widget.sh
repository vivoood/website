#!/bin/bash
filename=$1
echo '#ifndef '${filename^^}'_H
#define '${filename^^}'_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class '${filename}' : public Wt::WContainerWidget
{
private:
    friend class Factory;
    '${filename}' ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
};

#endif //'${filename^^}'_H
' > ${filename}.h

echo '#include "'${filename}'.h"

'${filename}'::'${filename}' ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::X * p = dynamic_cast<WidgetData::X*> ( pD );
    if ( p != nullptr )
    {

    }
}
' > ${filename}.cpp
