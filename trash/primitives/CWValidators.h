#ifndef CWVALIDATORS_H
#define CWVALIDATORS_H

#include <Wt/WValidator>

namespace CWValidators
{

class EmailValidator : public Wt::WValidator
{
public:
    EmailValidator();
    virtual Result validate ( const WT_USTRING& input ) const;
};

class UsernameValidator : public Wt::WValidator
{
public:
    UsernameValidator();
    virtual Result validate ( const WT_USTRING& input ) const;
};

class PasswordValidator : public Wt::WValidator
{
public:
    PasswordValidator();
    virtual Result validate ( const WT_USTRING& input ) const;
};

}

#endif // CWVALIDATORS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
