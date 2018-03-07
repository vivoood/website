#include "CWHowItWorks.h"

#include <Wt/WText>
#include <Wt/WBreak>

CWHowItWorks::CWHowItWorks ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "How it work" ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "Make a registration on our site using the registration form and fill in the required data." ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "Be sure to specify a current email to receive the most exclusive flight offers on a regular basis." ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "After completing the basic information about yourself," ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "please give us the basic parameters of your trips to get a clear idea of yy​​your desired flights." ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "For the final, please choose a type of subscription and how often you want to get personalized information about cheap airfares." ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "After completing all fields, you will be transferred to the next page to pay your chosen subscription with VISA and MasterCard." ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "That is all! Check out the best deals while you are drinking your morning coffee." ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "Plan your next trip at an awesome low price while relaxing in your home!" ) );
    this->addWidget ( new Wt::WBreak() );

}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
