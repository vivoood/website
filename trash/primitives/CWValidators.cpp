#include "CWValidators.h"

#include <boost/regex.hpp>
#include <algorithm>

CWValidators::UsernameValidator::UsernameValidator() : Wt::WValidator ( true )
{
    this->setInvalidBlankText ( "Insert your username" );
}

Wt::WValidator::Result CWValidators::UsernameValidator::validate ( const Wt::WString& input ) const
{
    std::string inputString = input.toUTF8();
    if ( inputString.size() >= 12 )
    {
        return Result ( Invalid, "must be less than 12 symbols" );
    }

    if ( inputString.empty() )
    {
        return Result ( Invalid, "must be not empty" );
    }

    return Result ( Valid );
}

CWValidators::EmailValidator::EmailValidator() : Wt::WValidator ( true )
{
    this->setInvalidBlankText ( "e-mail address is required" );
}

Wt::WValidator::Result CWValidators::EmailValidator::validate ( const Wt::WString& input ) const
{
    std::string inputString = input.toUTF8();
    if ( inputString.size() <= 5 )
    {
//         std::cout << "\n\n\n\n\n" << inputString << " > 4 \n\n\n\n"
        return Result ( Invalid, "must be more than 5 symbols" );
    }

    size_t nCount = std::count ( inputString.begin(), inputString.end(), '@' );
    if ( nCount != 1 )
    {
        return Result ( Invalid, "must be e-mail address" );
    }

    size_t nCountSpaces = std::count ( inputString.begin(), inputString.end(), ' ' );
    if ( nCountSpaces != 0 )
    {
        return Result ( Invalid, "e-mail address there should be no empty spaces" );
    }

    return Result ( Valid );
}

CWValidators::PasswordValidator::PasswordValidator() : Wt::WValidator ( true )
{
}

Wt::WValidator::Result CWValidators::PasswordValidator::validate ( const Wt::WString& input ) const
{
    std::string inputString = input.toUTF8();
    boost::regex e ( "([0-9]+)" );
    if ( boost::regex_match ( inputString , e ) == 0 )
        return Result ( Invalid, "password isn't valid" );

    return Result ( Valid );
}


// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
