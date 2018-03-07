#include "CWUser.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <crypto++/sha.h>

#include "CWUser.h"
#include "Debug.h"

namespace
{

std::string ConvertStr ( std::string str, bool tofile )
{
    if ( tofile )
        std::replace ( str.begin(), str.end(), ' ', ':' );
    else
        std::replace ( str.begin(), str.end(), ':', ' ' );

    return str;
}

}

CWUser::CWUser ( std::string user, std::string pass, std::string mail, std::string continent, std::string gender, std::string abon )
{
    if ( !user.empty() )
        _user = user;

    if ( !pass.empty() )
        _pass = pass;

    if ( !mail.empty() )
        _mail = mail;

    if ( !continent.empty() )
        _continent = continent;

    if ( !gender.empty() )
        _gender = gender;

    if ( !abon.empty() )
        _abonament = abon;
}

void CWUser::save()
{
    std::lock_guard<std::mutex> lock ( mtx );
    std::ofstream outfile ( "users/" + hash() );
    outfile << *this;
    outfile.close();
}

bool CWUser::load ( std::string filename )
{
    if ( filename.empty() )
        return false;

    std::string dir ( "users/" );
    dir.append ( filename );

    if ( ! CWUser::CheckUserExist ( filename ) )
        return false;

    std::ifstream infile ( dir );
    infile >> *this;
    infile.close();

    return true;
}

std::string CWUser::hash()
{
    return CWUser::CreateHash ( _mail + _pass );
}

bool CWUser::CheckUserExist ( std::string filename )
{
    std::ifstream infile ( "users/" + filename );
    bool bExist = infile.good();
    infile.close();
    return bExist;
}

bool CWUser::CheckOwner ( std::string filename )
{
    if ( filename == "9d4dc8d5d3bc30dfe5db75d9934be33b9e8d949b" )
        return true;
    return false;
}

std::string CWUser::CreateHash ( std::string s )
{
    std::string hstr = "5345@asd#" + s + "fslkdjf34";
    CryptoPP::SHA1 hash;
    unsigned char _sha1[ CryptoPP::SHA1::DIGESTSIZE ];
    hash.CalculateDigest ( _sha1, ( byte* ) s.c_str(), s.length() );

    const unsigned char * Bytes = _sha1;
    size_t Length = CryptoPP::SHA1::DIGESTSIZE;

    std::ostringstream os;
    os.fill ( '0' );
    os << std::hex;
    for ( const unsigned char * ptr=Bytes; ptr<Bytes+Length; ptr++ )
        os << std::setw ( 2 ) << ( unsigned int ) *ptr;

    return os.str();
}

std::ostream& operator<< ( std::ostream& os, const CWUser& dt )
{
    os << ConvertStr ( dt._user, true ) << std::endl;
    os << ConvertStr ( dt._pass, true ) << std::endl;
    os << ConvertStr ( dt._mail, true ) << std::endl;
    os << ConvertStr ( dt._continent, true ) << std::endl;
    os << ConvertStr ( dt._gender, true ) << std::endl;
    os << ConvertStr ( dt._abonament, true ) << std::endl;
    return os;
}

std::istream& operator>> ( std::istream& is, CWUser& dt )
{
    is >> dt._user;
    dt._user = ConvertStr ( dt._user, false );

    is >> dt._pass;
    dt._pass = ConvertStr ( dt._pass, false );

    is >> dt._mail;
    dt._mail = ConvertStr ( dt._mail, false );

    is >> dt._continent;
    dt._continent = ConvertStr ( dt._continent, false );

    is >> dt._gender;
    dt._gender = ConvertStr ( dt._gender, false );

    is >> dt._abonament;
    dt._abonament = ConvertStr ( dt._abonament, false );

    return is;
}

/** ### ############################################################################# */
/** ### ############################################################################# */
/** ### ############################################################################# */

std::ostream& operator<< ( std::ostream& os, const OffersData::SOffer& dt )
{
    os << ConvertStr ( dt._departure_continent, true ) << std::endl;
    os << ConvertStr ( dt._departure_city, true ) << std::endl;
    os << ConvertStr ( dt._departure_code, true ) << std::endl;
    os << ConvertStr ( dt._departure_date, true ) << std::endl;

    os << ConvertStr ( dt._arrival_continent, true ) << std::endl;
    os << ConvertStr ( dt._arrival_city, true ) << std::endl;
    os << ConvertStr ( dt._arrival_code, true ) << std::endl;
    os << ConvertStr ( dt._arrival_date, true ) << std::endl;

    os << ConvertStr ( dt._currency_code, true ) << std::endl;
    os << ConvertStr ( dt._cheap_price, true ) << std::endl;
    os << ConvertStr ( dt._normal_price, true ) << std::endl;
    os << ConvertStr ( dt._hyperlink, true ) << std::endl;

    os << ConvertStr ( dt._airline, true ) << std::endl;
    os << ConvertStr ( dt._direction, true ) << std::endl;
    os << ConvertStr ( dt._luggage, true ) << std::endl;
    os << ConvertStr ( dt._payload, true ) << std::endl;

    return os;
}

std::istream& operator>> ( std::istream& is, OffersData::SOffer& dt )
{
    is >> dt._departure_continent;
    dt._departure_continent = ConvertStr ( dt._departure_continent, false );
    is >> dt._departure_city;
    dt._departure_city = ConvertStr ( dt._departure_city, false );
    is >> dt._departure_code;
    dt._departure_code = ConvertStr ( dt._departure_code, false );
    is >> dt._departure_date;
    dt._departure_date = ConvertStr ( dt._departure_date, false );

    is >> dt._arrival_continent;
    dt._arrival_continent = ConvertStr ( dt._arrival_continent, false );
    is >> dt._arrival_city;
    dt._arrival_city = ConvertStr ( dt._arrival_city, false );
    is >> dt._arrival_code;
    dt._arrival_code = ConvertStr ( dt._arrival_code, false );
    is >> dt._arrival_date;
    dt._arrival_date = ConvertStr ( dt._arrival_date, false );

    is >> dt._currency_code;
    dt._currency_code = ConvertStr ( dt._currency_code, false );
    is >> dt._cheap_price;
    dt._cheap_price = ConvertStr ( dt._cheap_price, false );
    is >> dt._normal_price;
    dt._normal_price = ConvertStr ( dt._normal_price, false );
    is >> dt._hyperlink;
    dt._hyperlink = ConvertStr ( dt._hyperlink, false );

    is >> dt._airline;
    dt._airline = ConvertStr ( dt._airline, false );
    is >> dt._direction;
    dt._direction = ConvertStr ( dt._direction, false );
    is >> dt._luggage;
    dt._luggage = ConvertStr ( dt._luggage, false );
    is >> dt._payload;
    dt._payload = ConvertStr ( dt._payload, false );

    return is;
}

void OffersData::add ( OffersData::SOffer o )
{
    vFreeOffers.push_back ( o );
    offer_count = vFreeOffers.size();
}

void OffersData::del ( unsigned int id )
{
    if ( ! ( id < vFreeOffers.size() ) )
        return;

    vFreeOffers.erase ( vFreeOffers.begin() + id );
    offer_count = vFreeOffers.size();
}

void OffersData::save()
{
    std::lock_guard<std::mutex> lock ( mtx );
    std::ofstream outfile ( filename );
    outfile << *this;
    outfile.close();
}

bool OffersData::load()
{
    std::string dir ( filename );
    std::ifstream infile ( dir );
    infile >> *this;
    infile.close();
    return true;
}

std::ostream& operator<< ( std::ostream& os, const OffersData& dt )
{
    os << dt.offer_count << std::endl;
    for ( auto it : dt.vFreeOffers )
        os << it << std::endl;
    return os;
}

std::istream& operator>> ( std::istream& is, OffersData& dt )
{
    is >> dt.offer_count;
    for ( int i = 0; i < dt.offer_count; i++ )
    {
        OffersData::SOffer tmp;
        is >> tmp;
        dt.vFreeOffers.push_back ( tmp );
    }

    return is;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
