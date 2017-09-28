#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Wt/WWidget>

#include "IWidgetData.h"

class Constants
{
public:

    Constants();

    /** Header ******************************************* */

    /** @Header */
    WidgetData::SHeader m_Header;

    /** Body ********************************************* */

    /** @MainTable */
    WidgetData::STable m_Table;

    /** @MainButtons */
    WidgetData::STabs m_Tabs;

    /** @One @Offer */
    WidgetData::SOffers m_Offers;

    /** @Left @column */
    WidgetData::SLeftCol m_LeftCol;

    /** Footer ******************************************* */

    /** @Footer */
    WidgetData::SFooter m_Footer;

};

extern Constants gConstants;

#endif // CONSTANTS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
