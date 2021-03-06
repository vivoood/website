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
    WidgetData::STabs m_TabsOwner;
    WidgetData::SQuery m_Query;
    WidgetData::SMyQuery m_MyQuery;
    WidgetData::SContacts m_Contacts;
    WidgetData::SFaq m_Faq;


    /** @One @Offer */
    WidgetData::SOffer m_Offer;
    WidgetData::SOffersLeftRightBase m_OffersRight;
    WidgetData::SOffersLeftRightBase m_OffersLeft;

    /** @Left @column */
    WidgetData::SLeftCol m_LeftCol;
    WidgetData::SLeftCol m_LeftColAfterLogin;
    WidgetData::SLogin m_Login;

    /** @Account */
    WidgetData::SAccount m_MyAccount;
    WidgetData::SRadioButtons m_radioButtons;
    WidgetData::SContiCtry m_ContiCtry;

    /** @User-line-input */
    WidgetData::SUserInput m_UserLineInput;
    WidgetData::SUserInput m_UserComboInput;
    WidgetData::SUserInput m_ContiCtryInput;
    
    /** @Owner */
    WidgetData::SOwnerFreeOffers m_OwnerFreeOffers;

    /** Footer ******************************************* */

    /** @Footer */
    WidgetData::SFooter m_Footer;

};

#endif // CONSTANTS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
