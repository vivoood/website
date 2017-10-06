#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Wt/WWidget>

#include "IWidgetData.h"

class Constants
{
public:

    Constants();
    IWidgetData* GetData ( std::string str, std::string strHash = "n/a" );

private:

    std::map<std::string, IWidgetData*> m_mapData;

    /** Header ******************************************* */

    /** @Header */
    WidgetData::SHeader m_Header;

    /** Body ********************************************* */

    /** @MainTable */
    WidgetData::STable m_Table;
    WidgetData::STable m_TableAfterLogin;
    WidgetData::STable m_TableOwnerLogin;

    /** @MainButtons */
    WidgetData::STabs m_Tabs;
    WidgetData::STabs m_TabsAfterLogin;

    /** @One @Offer */
    WidgetData::SOffers m_Offers;

    /** @Left @column */
    WidgetData::SLeftCol m_LeftCol;
    WidgetData::SLeftCol m_LeftColAfterLogin;
    WidgetData::SLogin m_Login;

    /** @Account */
    WidgetData::SAccount m_MyAccount;

    /** @User-line-input */
    WidgetData::SUserInput m_UserLineInput;
    WidgetData::SUserInput m_UserComboInput;

    /** Footer ******************************************* */

    /** @Footer */
    WidgetData::SFooter m_Footer;

};

extern Constants gConstants;

#endif // CONSTANTS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
