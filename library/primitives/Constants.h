#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

class Constants
{
public:
    
    struct STabData
    {
        std::string strTabName;
        std::string strTabTemplateId;
        std::vector<std::string> vTabDescr;
    };
    
    Constants();
    std::string strSiteName;
    std::string strSiteSlogan;
    std::vector<STabData> vTabs;
    STabData emptyTabData;
    
    const STabData & FindTabData( std::string strKey );
};

extern Constants gConstants;

#endif // CONSTANTS_H
