#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Wt/WWidget>
#include <string>
#include <vector>

class Constants
{
public:

    struct STabButtonsData
    {
        std::string strTabName;
        std::string strTabTemplateId;
        std::vector<std::string> vTabDescr;
    };

    struct STableData
    {
        std::string strStyle;
        std::string strLenght;
        std::string strWidgetName;
    };

    Constants();
    std::string strSiteName;
    std::string strSiteSlogan;
    std::vector<STabButtonsData> vMenuButtons;
    STabButtonsData emptyTabData;
    std::vector< std::vector< STableData > > vTable;

    const STabButtonsData & FindTabData ( std::string strKey );
};

extern Constants gConstants;

#endif // CONSTANTS_H
