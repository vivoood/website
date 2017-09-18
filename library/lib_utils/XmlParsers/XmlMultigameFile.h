#ifndef XMLMULTIGAMEFILE_H
#define XMLMULTIGAMEFILE_H

#include <map>
#include <string>

#include "XmlReadFile.h"

namespace pugi
{
    class xml_node;
}

class XmlMultigameFile: public XmlReadFile
{
public:
    XmlMultigameFile();
    ~XmlMultigameFile();
    
    bool ReadGamesPath(std::map<unsigned, std::string> & mGamesPath);

private:
    void CheckNode(const pugi::xml_node& node, std::map<unsigned, std::string> & mGamesPath);
};

#endif // XMLMULTIGAMEFILE_H
