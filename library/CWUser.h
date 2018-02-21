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

    std::string _user = "unknown_user";
    std::string _pass = "unknown_pass";
    std::string _mail = "unknown_mail";
    std::string _country = "unknown_country";
    std::string _gender = "unknown_gender";

    std::mutex mtx;
    friend std::ostream& operator<< ( std::ostream& os, const CWUser& dt );
    friend std::istream& operator>> ( std::istream& is, CWUser& dt );
};

class OffersBase
{
protected:
    std::string filename = "unknown_file";
public:
    OffersBase ( std::string fname ) : filename ( fname ) {}
};

class OffersData : public OffersBase
{
public:

    struct SOffer
    {
        SOffer() {}
        void set ( std::string d, std::string a, std::string cp, std::string np )
        {
            departure = d;
            arrival = a;
            cheap_price = cp;
            normal_price = np;
        }

        std::string departure = "unknown_departure";
        std::string arrival = "unknown_arrival";
        std::string cheap_price = "unknown_price";
        std::string normal_price = "unknown_price";
        friend std::ostream& operator<< ( std::ostream& os, const SOffer& dt );
        friend std::istream& operator>> ( std::istream& is, SOffer& dt );
    };

    OffersData ( std::string fname ) : OffersBase ( fname ) {}
    void add ( SOffer o );
    std::mutex mtx;
    void save();
    bool load ();

    int offer_count = 0;
    std::vector<SOffer> vFreeOffers;

    friend std::ostream& operator<< ( std::ostream& os, const OffersData& dt );
    friend std::istream& operator>> ( std::istream& is, OffersData& dt );
};

#endif //CWUSER_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 



