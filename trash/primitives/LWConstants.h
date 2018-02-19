#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Wt/WWidget>

#include "IWidgetData.h"

class LWConstants
{
public:
    
    LWConstants();
    IWidgetData* GetData ( std::string str, std::string strHash = "n/a" );

private:

    std::map<std::string, IWidgetData*> m_mapData;
    WidgetData::STable m_Table;
};

#endif // CONSTANTS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
