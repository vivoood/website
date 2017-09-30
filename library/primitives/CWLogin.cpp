#include "CWLogin.h"

#include <Wt/WLineEdit>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

//#include <crypto++/sha.h>

#include "CWSignals.h"

CWLogin::CWLogin ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SLogin * p = dynamic_cast<WidgetData::SLogin*> ( pD );
    if ( p != nullptr )
    {
        Wt::WText * pUserLabel = new Wt::WText ( "Username" );
        pUserLabel->setStyleClass ( p->strStyleFields );
        this->addWidget ( pUserLabel );

        Wt::WLineEdit * pUserEdit = new Wt::WLineEdit();
        pUserEdit->setStyleClass ( p->strStyleFields );
        this->addWidget ( pUserEdit );

        this->addWidget ( new Wt::WBreak() );

        Wt::WText * pPassLabel = new Wt::WText ( "Password" );
        pPassLabel->setStyleClass ( p->strStyleFields );
        this->addWidget ( pPassLabel );

        Wt::WLineEdit * pPassEdit = new Wt::WLineEdit();
        pPassEdit->setEchoMode ( Wt::WLineEdit::Password );
        pPassEdit->setStyleClass ( p->strStyleFields );
        this->addWidget ( pPassEdit );

        this->addWidget ( new Wt::WBreak() );

        Wt::WPushButton * pLoginBtn = new Wt::WPushButton ( "Login" );
        pLoginBtn->setStyleClass ( p->strStyleBtns );
        pLoginBtn->clicked().connect ( std::bind ( [=]()
        {
//            CryptoPP::SHA1 hash;
//            unsigned char arrLoginSha1[ CryptoPP::SHA1::DIGESTSIZE ];
//            std::string strNamePass ( "user" );
//            strNamePass.append ( "Pass" );
 //           hash.CalculateDigest ( arrLoginSha1, ( byte* ) strNamePass.c_str(), strNamePass.length() );
            gCWSignals.signallogintomainwidget.emit();
        } ) );
        this->addWidget ( pLoginBtn );

        Wt::WPushButton * pRegBtn = new Wt::WPushButton ( "Register" );
        pRegBtn->setStyleClass ( p->strStyleBtns );
        pRegBtn->clicked().connect ( std::bind ( [=]()
        {
            gCWSignals.signallogintotabs.emit ( "CWRegisterAccount", nullptr );
        } ) );
        this->addWidget ( pRegBtn );

        this->setStyleClass ( p->strStyleCommon );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
