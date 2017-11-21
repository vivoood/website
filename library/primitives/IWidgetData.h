#ifndef IWIDGETDATA_H
#define IWIDGETDATA_H

#include <string>
#include <vector>

class IWidgetData
{
public:
    std::string strHash = "n/a";
    virtual ~IWidgetData() {}
};

namespace WidgetData
{

struct SHeader : public IWidgetData
{
    std::string strStyle = "web-site-name-style";
};

struct STabButtonsData : public IWidgetData
{
    std::string strTabName = "n/a";
    std::string strTabButtonStyle = "n/a";
    std::string strChildWidget = "n/a";
    std::string strChildWidgetData = "n/a";
};

struct STabs : public IWidgetData
{
    std::string strTabStyle;
    std::vector<STabButtonsData> vTabButtons;
};

struct STableData : public IWidgetData
{
    std::string strBgrImg = "n/a";
    std::string strStyle;
    std::string strLenght;
    std::string strWidgetName;
    std::string strWidgetData;
};

struct STable : public IWidgetData
{
    std::vector< std::vector<WidgetData::STableData> > vTable;
};

struct SFooter : public IWidgetData
{
    std::string strStyle;
};

struct SOffer : public IWidgetData
{
    std::string strStyle = "default-offer-style";
    std::string strBtnStyle = "default-offer-button-style";
    std::string strBtnInsteadStyle = "default-offer-button-instead-style";
    std::string strBigStyle = "default-offer-big-style";
};

struct SOffersLeftRightBase : public IWidgetData
{
    static const int cnLeftSize = 4;
    static const int cnRightSize = 5;
    std::vector<std::string> m_OffersHashList;
};

struct SRegister : public IWidgetData
{
    std::string strStyleError = "n/a";
    std::string strStyleButton = "n/a";
};

struct SLogin : public IWidgetData
{
    std::string strStyleCommon = "n/a";
    std::string strStyleFields = "n/a";
    std::string strStyleBtns = "n/a";
    SRegister _register;
};

struct SLeftCol : public IWidgetData
{
    std::vector< std::pair< std::string, std::string > > m_vWidgets;
};

struct SUserInput : public IWidgetData
{
    std::string strStyleContainer = "n/a";
    std::string strStyleLabel = "n/a";
    std::string strStyleLineEdit = "n/a";
};

struct SAccount : public IWidgetData
{
    std::string strStyle;
};

struct SRadioButtons : public IWidgetData
{
    std::string strStyle;
    std::string strMainMsg;
    std::vector< std::pair < std::string, std::string > > content;
};

struct SContiCtry : public IWidgetData
{
    std::string strStyle;
    std::map< std::string, std::vector< std::string > & > _list;
};

struct SQuery : public IWidgetData
{
};

struct SMyQuery : public IWidgetData
{
};

struct SContacts : public IWidgetData
{
    std::string strContainerStyle = "contacts-style";
};

struct SFaq : public IWidgetData
{
    std::string strContainerStyle = "faq-style";
};

struct SOwnerFreeOffers : public IWidgetData
{
    enum class EID
    {
        from = 0, to, price, instead, airl, oneway, direct, link
    };

    struct Data
    {
        EID id;
        std::string label;
        std::string widget;
        std::string style;
    };

    std::vector<SOwnerFreeOffers::Data> v;
    std::string Find ( EID id )
    {
        for ( unsigned int i = 0; i < v.size(); i++ )
        {
            if ( v[i].id == id )
            {
                return v[i].label;
            }
        }
    }
};

}

typedef WidgetData::SOwnerFreeOffers::EID OwnerEID;

#endif // IWIDGETDATA_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
