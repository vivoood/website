#ifndef IWIDGETDATA_H
#define IWIDGETDATA_H

#include <string>
#include <vector>

class IWidgetData
{
public:
    std::string strUserHash = "n/a";
    std::string strStyleClass = "n/a";
    virtual ~IWidgetData() {}
};

namespace WidgetData
{

}

#endif // IWIDGETDATA_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
