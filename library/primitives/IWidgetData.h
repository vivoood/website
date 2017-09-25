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

struct STabButtonsData : public IWidgetData
{
    std::string strTabName;
    std::string strTabButtonStyle;
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
    std::string strFrom = "n/a";
    std::string strTo = "n/a";
    std::string strAirline = "n/a";
    std::string strPrice = "$ 0";
    std::string strStyle = "default-offer-style";
    std::string strBtnStyle = "default-offer-button-style";
    bool bOneWay = false;
    bool bDirectFlight = false;
};

struct SOffers : public IWidgetData
{
    std::vector<SOffer> m_Offers;
};

}

#endif // IWIDGETDATA_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
