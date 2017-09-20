#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Wt/WWidget>

#include "IWidgetData.h"

class Constants
{
public:

    Constants();

    /** Header */
    std::string strSiteName;
    std::string strSiteSlogan;

    /** Body ********************************************* */

    /** @MainTable */
    WidgetData::STable m_Table;

    /** @MainButtons */
    WidgetData::STabs m_Tabs;



    /** Footer */
};

extern Constants gConstants;

#endif // CONSTANTS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
