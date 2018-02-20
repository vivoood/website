#!/bin/bash
filename=$1
echo '#ifndef '${filename^^}'_H
#define '${filename^^}'_H

#include <Wt/WContainerWidget>

class '${filename}' : public Wt::WContainerWidget
{
private:
    friend class Factory;
    '${filename}' ( std::string usrhash, Wt::WContainerWidget* parent = 0 );
};

#endif //'${filename^^}'_H
' > ${filename}.h

echo '#include "'${filename}'.h"

#include <Wt/WText>

'${filename}'::'${filename}' ( std::string usrhash, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( new Wt::WText ("'${filename}'") );
}
' > ${filename}.cpp
