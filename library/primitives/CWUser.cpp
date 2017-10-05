#include "CWUser.h"

#include "CWHash.h"

CWUser::CWUser ( std::string user, std::string sha, std::string mail, std::string coutry, std::string gender )
{
    _user = user;
    _sha = sha;
    _mail = mail;
    _country = coutry;
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
    return CWHash::Get ( _user + _sha );
}

std::string CWUser::user()
{
    return _user;
}

bool CWUser::CheckUserExist ( std::string filename )
{
    std::ifstream infile ( "users/" + filename );
    bool bExist = infile.good();
    infile.close();
    return bExist;
}

std::ostream& operator<< ( std::ostream& os, const CWUser& dt )
{
    os << dt._user << "," << dt._sha << "," << dt._mail << "," << dt._country << "," << dt._gender;
    return os;
}

std::istream& operator>> ( std::istream& is, CWUser& dt )
{
    std::string str;
    is >> str;

    std::istringstream ss ( str );
    std::getline ( ss, dt._user, ',' );
    std::getline ( ss, dt._sha, ',' );
    std::getline ( ss, dt._mail, ',' );
    std::getline ( ss, dt._country, ',' );
    std::getline ( ss, dt._gender, ',' );

    return is;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 






