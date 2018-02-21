#include "CWUser.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <crypto++/sha.h>

#include "CWUser.h"

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

CWUser::CWUser ( std::string user, std::string pass, std::string mail, std::string coutry, std::string gender )
{
    if ( !user.empty() )
        _user = user;

    if ( !pass.empty() )
        _pass = pass;

    if ( !mail.empty() )
        _mail = mail;

    if ( !coutry.empty() )
        _country = coutry;

    if ( !gender.empty() )
        _gender = gender;
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
    os << ConvertStr ( dt._country, true ) << std::endl;
    os << ConvertStr ( dt._gender, true ) << std::endl;
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

    is >> dt._country;
    dt._country = ConvertStr ( dt._country, false );

    is >> dt._gender;
    dt._gender = ConvertStr ( dt._gender, false );

    return is;
}

/** ### ############################################################################# */
/** ### ############################################################################# */
/** ### ############################################################################# */

std::ostream& operator<< ( std::ostream& os, const FreeOffersData::SOffer& dt )
{
    os << ConvertStr ( dt.departure, true ) << std::endl;
    os << ConvertStr ( dt.arrival, true ) << std::endl;
    os << ConvertStr ( dt.cheap_price, true ) << std::endl;
    os << ConvertStr ( dt.normal_price, true ) << std::endl;
    return os;
}

std::istream& operator>> ( std::istream& is, FreeOffersData::SOffer& dt )
{
    is >> dt.departure;
    dt.departure = ConvertStr ( dt.departure, false );

    is >> dt.arrival;
    dt.arrival = ConvertStr ( dt.arrival, false );

    is >> dt.cheap_price;
    dt.cheap_price = ConvertStr ( dt.cheap_price, false );

    is >> dt.normal_price;
    dt.normal_price = ConvertStr ( dt.normal_price, false );

    return is;
}

void FreeOffersData::add ( FreeOffersData::SOffer o )
{
    load();
    vFreeOffers.push_back ( o );
    offer_count = vFreeOffers.size();
    save();
}

void FreeOffersData::save()
{
    std::lock_guard<std::mutex> lock ( mtx );
    std::ofstream outfile ( "owner/free_offers" );
    outfile << *this;
    outfile.close();
}

bool FreeOffersData::load()
{
    std::string dir ( "owner/free_offers" );
    std::ifstream infile ( dir );
    infile >> *this;
    infile.close();
    return true;
}

std::ostream& operator<< ( std::ostream& os, const FreeOffersData& dt )
{
    os << dt.offer_count << std::endl;
    for ( auto it : dt.vFreeOffers )
        os << it << std::endl;
    return os;
}

std::istream& operator>> ( std::istream& is, FreeOffersData& dt )
{
    is >> dt.offer_count;
    for ( int i = 0; i < dt.offer_count; i++ )
    {
        FreeOffersData::SOffer tmp;
        is >> tmp;
        dt.vFreeOffers.push_back ( tmp );
    }

    return is;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
