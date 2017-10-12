#include "CWUser.h"

#include "CWHash.h"

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
    if ( filename == "88b8216858cc70dfa70f4a112a2cbd4797f313f6" )
        return true;
    return false;
}

std::ostream& operator<< ( std::ostream& os, const CWUser& dt )
{
    os << dt._user << std::endl;
    os << dt._pass << std::endl;
    os << dt._mail << std::endl;
    os << dt._country << std::endl;
    os << dt._gender << std::endl;
    os << dt._abonCnt << std::endl;
    for ( auto it : dt._vAbon )
        os << it << std::endl;;
    return os;
}

std::istream& operator>> ( std::istream& is, CWUser& dt )
{
    is >> dt._user;
    is >> dt._pass;
    is >> dt._mail;
    is >> dt._country;
    is >> dt._gender;
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
    os << dt._date << std::endl;
    os << dt._adults << std::endl;
    os << dt._budget << std::endl;
    os << dt._payd;
    return os;
}

std::istream& operator>> ( std::istream& is, CWUser::SAbon& dt )
{
    is >> dt._abon;
    is >> dt._from;
    is >> dt._to;
    is >> dt._date;
    is >> dt._adults;
    is >> dt._budget;
    is >> dt._payd;
    return is;
}

std::ostream& operator<< ( std::ostream& os, const CWUser::SContiCtry& dt )
{
    os << dt._conti << std::endl;
    os << dt._ctry << std::endl;
    os << dt._city;
    return os;
}

std::istream& operator>> ( std::istream& is, CWUser::SContiCtry& dt )
{
    is >> dt._conti;
    is >> dt._ctry;
    is >> dt._city;
    return is;
}

void CWUser::print()
{
    std::cout << "User: " << _user << std::endl;
    std::cout << "Pass: " << _pass << std::endl;
    std::cout << "Mail: " << _mail << std::endl;
    std::cout << "Ctry: " << _country << std::endl;
    std::cout << "Gndr: " << _gender << std::endl;

    for ( const auto & it : _vAbon )
    {
        std::cout << "#" << it._abon << std::endl;
        std::cout << "#" << it._from._conti << " " << it._from._ctry << " " << it._from._city << std::endl;
        std::cout << "#" << it._to._conti << " " << it._to._ctry << " " << it._to._city << std::endl;
        std::cout << "#" << it._date << std::endl;
        std::cout << "#" << it._adults << std::endl;
        std::cout << "#" << it._budget << std::endl;
        std::cout << "#" << ( it._payd ? "payd" : "not payd" ) << std::endl;
    }
}


// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
