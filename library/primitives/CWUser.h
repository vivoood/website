#ifndef CWUSER_H
#define CWUSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <mutex>

#include <iostream>

class CWUser
{
public:

    struct SContiCtry
    {
        std::string _conti = "n/a";
        std::string _ctry = "n/a";
        std::string _city = "n/a";
        std::string Export()
        {
            return _conti + " / " + _ctry + " / " + _city;
        }
    };

    struct SAbon
    {
        int         _abon = 0;
        SContiCtry  _from;
        SContiCtry  _to;
        std::string _date = "n/a";
        std::string _adults = "n/a";
        std::string _budget = "n/a";
        bool        _payd = false;
        void Normalize();
        std::vector<std::string> Export();
        std::vector<std::string> GetHeaders();
    };

    CWUser() {}
    CWUser ( std::string user, std::string sha, std::string mail, std::string coutry, std::string gender );
    void save();
    bool load ( std::string filename );
    std::string hash();
    void AddAbon ( SAbon a )
    {
        _vAbon.push_back ( a );
        _abonCnt = _vAbon.size();
    }

    static bool CheckUserExist ( std::string filename );
    static bool CheckOwner ( std::string filename );
    std::vector<std::vector<std::string>> ExportAbonaments ( CWUser & ref );

//     void print();

// private:
    friend class CWAfterLogin;
    friend class CWLogin;
    friend class CWRegisterAccount;
    friend class CWQuery;
    friend class CWMyQueries;

    std::string _user = "n/a";
    std::string _pass = "n/a";
    std::string _mail = "n/a";
    std::string _country = "n/a";
    std::string _gender = "n/a";
    int         _abonCnt = 0;
    std::vector<SAbon> _vAbon;

    std::mutex mtx;
    friend std::ostream& operator<< ( std::ostream& os, const CWUser& dt );
    friend std::istream& operator>> ( std::istream& is, CWUser& dt );
    friend std::ostream& operator<< ( std::ostream& os, const CWUser::SAbon& dt );
    friend std::istream& operator>> ( std::istream& is, CWUser::SAbon& dt );
    friend std::ostream& operator<< ( std::ostream& os, const CWUser::SContiCtry& dt );
    friend std::istream& operator>> ( std::istream& is, CWUser::SContiCtry& dt );
};

#endif //CWUSER_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 



