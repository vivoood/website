#include "CWUser.h"

#include <algorithm>

#include "CWHash.h"
#include "Factory.h"

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

CWUser::CWUser ( std::string user, std::string sha, std::string mail, std::string coutry, std::string gender )
{
    if ( !user.empty() )
        _user = user;

    if ( !sha.empty() )
        _pass = sha;

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
    return CWHash::Get ( _mail );
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
    if ( filename == "43e0f29aa1f2e636542c65cbaa8690ca97749b4d" )
        return true;
    return false;
}

std::vector<std::vector<std::string>> CWUser::ExportAbonaments ( CWUser& ref )
{
    std::vector<std::vector<std::string>> v;

    std::vector<std::string> headers;
    if ( !ref._vAbon.empty() )
        v.push_back ( ref._vAbon.front().GetHeaders() );

    std::vector<SAbon> & ab = ref._vAbon;
    for ( auto & i : ab )
        v.push_back ( i.Export() );

    return v;
}

std::ostream& operator<< ( std::ostream& os, const CWUser& dt )
{
    os << ConvertStr ( dt._user, true ) << std::endl;
    os << ConvertStr ( dt._pass, true ) << std::endl;
    os << ConvertStr ( dt._mail, true ) << std::endl;
    os << ConvertStr ( dt._country, true ) << std::endl;
    os << ConvertStr ( dt._gender, true ) << std::endl;
    os << dt._abonCnt << std::endl;
    for ( auto it : dt._vAbon )
        os << it << std::endl;;
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

    is >> dt._abonCnt;
    for ( int i = 0; i < dt._abonCnt; i++ )
    {
        CWUser::SAbon tmp;
        is >> tmp;
        dt._vAbon.push_back ( tmp );
    }

    return is;
}

std::ostream& operator<< ( std::ostream& os, const CWUser::SAbon& dt )
{
    os << dt._abon << std::endl;
    os << dt._from << std::endl;
    os << dt._to << std::endl;
    os << ConvertStr ( dt._date, true ) << std::endl;
    os << ConvertStr ( dt._adults, true ) << std::endl;
    os << ConvertStr ( dt._budget, true ) << std::endl;
    os << dt._payd;
    return os;
}

std::istream& operator>> ( std::istream& is, CWUser::SAbon& dt )
{
    is >> dt._abon;
    is >> dt._from;
    is >> dt._to;

    is >> dt._date;
    dt._date = ConvertStr ( dt._date, false );

    is >> dt._adults;
    dt._adults = ConvertStr ( dt._adults, false );

    is >> dt._budget;
    dt._budget = ConvertStr ( dt._budget, false );

    is >> dt._payd;
    return is;
}

std::ostream& operator<< ( std::ostream& os, const CWUser::SContiCtry& dt )
{
    os << ConvertStr ( dt._conti, true ) << std::endl;
    os << ConvertStr ( dt._ctry, true ) << std::endl;
    os << ConvertStr ( dt._city, true );
    return os;
}

std::istream& operator>> ( std::istream& is, CWUser::SContiCtry& dt )
{
    is >> dt._conti;
    dt._conti = ConvertStr ( dt._conti, false );

    is >> dt._ctry;
    dt._ctry = ConvertStr ( dt._ctry, false );

    is >> dt._city;
    dt._city = ConvertStr ( dt._city, false );

    return is;
}

void CWUser::SAbon::Normalize()
{
    if ( _from._city.empty() )
        _from._city = "n/a";

    if ( _to._city.empty() )
        _to._city = "n/a";

    if ( _adults.empty() )
        _adults = "n/a";

    if ( _budget.empty() )
        _budget = "n/a";
}

std::vector<std::string> CWUser::SAbon::Export()
{
    std::vector<std::string> abonam = { "2.99$", "4.99$", "9.99$" };

    std::vector<std::string> v;
    v.push_back ( _from.Export() );
    v.push_back ( _to.Export() );
    v.push_back ( _date );
    v.push_back ( _adults );
    v.push_back ( _budget );
    v.push_back ( abonam[_abon] );
    return v;
}

std::vector<std::string> CWUser::SAbon::GetHeaders()
{
    std::vector<std::string> v;
    v.push_back ( "From" );
    v.push_back ( "To" );
    v.push_back ( "Date" );
    v.push_back ( "Adults" );
    v.push_back ( "Budget" );
    v.push_back ( "Price" );
    return v;
}

// void CWUser::print()
// {
//     std::cout << "User: " << _user << std::endl;
//     std::cout << "Pass: " << _pass << std::endl;
//     std::cout << "Mail: " << _mail << std::endl;
//     std::cout << "Ctry: " << _country << std::endl;
//     std::cout << "Gndr: " << _gender << std::endl;
//
//     for ( const auto & it : _vAbon )
//     {
//         std::cout << "#" << it._abon << std::endl;
//         std::cout << "#" << it._from._conti << " " << it._from._ctry << " " << it._from._city << std::endl;
//         std::cout << "#" << it._to._conti << " " << it._to._ctry << " " << it._to._city << std::endl;
//         std::cout << "#" << it._date << std::endl;
//         std::cout << "#" << it._adults << std::endl;
//         std::cout << "#" << it._budget << std::endl;
//         std::cout << "#" << ( it._payd ? "payd" : "not payd" ) << std::endl;
//     }
// }


// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
