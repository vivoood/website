#include "CWFaq.h"

#include <Wt/WText>
#include <Wt/WBreak>

CWFaq::CWFaq ( std::string usrhash, std::string strPayload, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "What will you get from us?" ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "Against the amount you paid for the selected subscription," ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "you will receive directly in your email accurate, " ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "systematized information on cheap flights to every corner of the world." ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "With just one check of your mail," ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "you will receive up-to-date offers without wasting time on airline sites." ) );
    this->addWidget ( new Wt::WBreak() );

    this->addWidget ( new Wt::WText ( "We will do this instead of your daily and tireless work. Trust us today!" ) );
    this->addWidget ( new Wt::WBreak() );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
