#ifndef CWUSER_H
#define CWUSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <mutex>

class CWUser
{
public:
    CWUser() {}
    CWUser ( std::string user, std::string sha, std::string mail, std::string coutry, std::string gender );
    void save();
    bool load ( std::string filename );
    std::string hash();
    std::string user();
    static bool CheckUserExist ( std::string filename );
private:
    std::mutex mtx;
    std::string _user = "n/a";
    std::string _sha = "n/a";
    std::string _mail = "n/a";
    std::string _country = "n/a";
    std::string _gender = "n/a";
    friend std::ostream& operator<< ( std::ostream& os, const CWUser& dt );
    friend std::istream& operator>> ( std::istream& is, CWUser& dt );
};

#endif //CWUSER_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


