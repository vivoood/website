#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

class Constants
{
public:
    Constants();
    std::string strSiteName;
    std::string strSiteSlogan;
    std::vector<std::pair<std::string, std::string>> vTabs;
};

extern Constants gConstants;

#endif // CONSTANTS_H
