#ifndef XMLGAMEFILE_H
#define XMLGAMEFILE_H
#include "XmlReadFile.h"


#include <map>

class XmlGameFile :public XmlReadFile
{
public:
    XmlGameFile();
    ~XmlGameFile();
    

    //void DBG_DELETE_ME_DO_MULTIGAME_TEST();
    //void EXTRACT_GAMES(std::map<int, std::string>& outMap);


    /**
    * Get description of suported langauges 
    * @param [out] vecGames - vector of languages "EN" "BG" 
    * @return true on success
    */
    bool GetLanguages ( std::vector<std::string>& vLanguages ) const;
};

#endif // XMLGAMEFILE_H
