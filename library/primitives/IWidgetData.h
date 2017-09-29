#ifndef IWIDGETDATA_H
#define IWIDGETDATA_H

#include <string>
#include <vector>

class IWidgetData
{
public:
    virtual ~IWidgetData() {}
};

namespace WidgetData
{

struct SHeader : public IWidgetData
{
    std::string strTemplateName;
    std::string strBindName;
    std::string strBindSlogan;
    std::string strTitle;
    std::string strSlogan;
};

struct STabButtonsContentData : public IWidgetData
{
    std::string strChildWidget = "n/a";
    std::string strWidgetStyle;
};

struct STabButtonsData : public IWidgetData
{
    std::string strTabName;
    std::string strTabButtonStyle;
    STabButtonsContentData content;
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

struct SOfferBig : public IWidgetData
{
    std::string strFrom = "n/a";
    std::string strTo = "n/a";
    std::string strAirline = "n/a";
    std::string strPrice = "$ 0";
    std::string strStyle = "default-offer-big-style";
    bool bOneWay = false;
    bool bDirectFlight = false;
    std::string strHyperlink = "n/a";
};

struct SOffer : public IWidgetData
{
    SOfferBig offerBig;
    std::string strStyle = "default-offer-style";
    std::string strBtnStyle = "default-offer-button-style";
};

struct SOffers : public IWidgetData
{
    std::vector<SOffer> m_Offers;
};

struct SLogin : public IWidgetData
{
    std::string strStyleCommon = "n/a";
    std::string strStyleFields = "n/a";
    std::string strStyleBtns = "n/a";
};

struct SLeftCol : public IWidgetData
{
    std::vector< std::pair< std::string, std::string > > m_vWidgets;
};

struct SUserLineInput : public IWidgetData
{
    std::string strStyleContainer = "n/a";
    std::string strStyleLabel = "n/a";
    std::string strStyleLineEdit = "n/a";
};

}

#endif // IWIDGETDATA_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
