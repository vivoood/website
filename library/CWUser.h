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
    CWUser() {}
    CWUser ( std::string user, std::string pass, std::string mail, std::string coutry, std::string gender );
    void save();
    bool load ( std::string filename );
    std::string hash();

    static bool CheckUserExist ( std::string filename );
    static bool CheckOwner ( std::string filename );
    static std::string CreateHash ( std::string s );

    std::string _user = "n/a";
    std::string _pass = "n/a";
    std::string _mail = "n/a";
    std::string _country = "n/a";
    std::string _gender = "n/a";

    std::mutex mtx;
    friend std::ostream& operator<< ( std::ostream& os, const CWUser& dt );
    friend std::istream& operator>> ( std::istream& is, CWUser& dt );
};

class FreeOffersData
{
public:

    struct SOffer
    {
        SOffer() {}
        SOffer ( std::string d, std::string a, std::string cp, std::string np ) : departure ( d ), arrival ( a ), cheap_price ( cp ), normal_price ( np ) {}

        std::string departure = "n/a";
        std::string arrival = "n/a";
        std::string cheap_price = "n/a";
        std::string normal_price = "n/a";
        friend std::ostream& operator<< ( std::ostream& os, const SOffer& dt );
        friend std::istream& operator>> ( std::istream& is, SOffer& dt );
    };

    FreeOffersData() {}
    void add ( SOffer o );
    std::mutex mtx;
    void save();
    bool load ();

    int offer_count = 0;
    std::vector<SOffer> vFreeOffers;

    friend std::ostream& operator<< ( std::ostream& os, const FreeOffersData& dt );
    friend std::istream& operator>> ( std::istream& is, FreeOffersData& dt );
};

#endif //CWUSER_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

