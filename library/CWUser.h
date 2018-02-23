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

        void set_departure ( std::string dc, std::string d, std::string dcode, std::string ddate )
        {
            _departure_continent = dc;
            _departure_city = d;
            _departure_code = dcode;
            _departure_date = ddate;
        }

        void set_arrival ( std::string ac, std::string a, std::string acode, std::string adate )
        {
            _arrival_continent = ac;
            _arrival_city = a;
            _arrival_code = acode;
            _arrival_date = adate;
        }

        void set_prices ( std::string c, std::string cpr, std::string norpr )
        {
            _currency_code = c;
            _cheap_price = cpr;
            _normal_price = norpr;
        }

        void set_options ( std::string a, std::string d, std::string l, std::string p )
        {
            _airline = a;
            _direction = d;
            _luggage = l;
            _payload = p;
        }

        std::string _departure_continent = "unknown_departure_cont";
        std::string _departure_city = "unknown_departure";
        std::string _departure_code = "unknown_departure_code";
        std::string _departure_date = "unknown_departure_date";

        std::string _arrival_continent = "unknown_arrival_cont";
        std::string _arrival_city = "unknown_arrival";
        std::string _arrival_code = "unknown_arrival_code";
        std::string _arrival_date = "unknown_arrival_date";

        std::string _currency_code = "unknown_currency_code";
        std::string _cheap_price = "unknown_price";
        std::string _normal_price = "unknown_price";

        std::string _airline = "unknown_airline";
        std::string _direction = "unknown_direction";
        std::string _luggage = "unknown_luggage";
        std::string _payload = "unknown_payload";

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



