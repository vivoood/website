#include "CWLoginCell.h"

#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>
#include <Wt/WLineEdit>

#include "CWUser.h"
#include "CWLineEditField.h"
#include "CWSignals.h"

CWLoginCell::CWLoginCell ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    parent->setContentAlignment ( Wt::AlignRight );

    this->addWidget ( new Wt::WBreak() );
    if ( usrhash == "Guest" )
    {
        Wt::WPushButton * pLoginBtn = new Wt::WPushButton ( "Login" );
        Wt::WPushButton * pSigninBtn = new Wt::WPushButton ( "Sign in" );

        this->addWidget ( new Wt::WText ( "Welcome " + usrhash ) );
        this->addWidget ( new Wt::WBreak() );

        CWLineEditField * usrn = new CWLineEditField ( "Username: ", this );
        this->addWidget ( usrn );

        CWLineEditField * passwd = new CWLineEditField ( "Password: ", this );
        this->addWidget ( passwd );

        this->addWidget ( pLoginBtn );
        this->addWidget ( pSigninBtn );

        pLoginBtn->clicked().connect ( std::bind ( [=]()
        {
            std::string mail = usrn->Value();
            std::string pass = passwd->Value();
            std::string uhash = CWUser::CreateHash ( mail + pass );
            if ( CWUser::CheckUserExist ( uhash ) )
            {
                gCWSignals.signal_create_center_column.emit ( uhash, "no_payload" );
            }
            else
            {
                this->addWidget ( new Wt::WText ( "Wrong email or password" ) );
                this->addWidget ( new Wt::WBreak() );
                this->addWidget ( new Wt::WBreak() );
            }
        } ) );

        pSigninBtn->clicked().connect ( std::bind ( [=]()
        {
            gCWSignals.signal_create_center_column.emit ( "SignIn", "no_payload" );
        } ) );

    }
    else
    {
        CWUser u;
        u.load ( usrhash );

        this->addWidget ( new Wt::WText ( std::string ( "Welcome " ) + u._user ) );
        this->addWidget ( new Wt::WBreak() );

        Wt::WPushButton * pLogoutBtn = new Wt::WPushButton ( "Logout" );
        pLogoutBtn->clicked().connect ( std::bind ( [=]()
        {
            gCWSignals.signal_create_center_column.emit ( "Guest", "show_free_offers_random" );
        } ) );
        this->addWidget ( pLogoutBtn );
    }
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );

}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


