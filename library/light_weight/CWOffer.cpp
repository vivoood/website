#include "CWOffer.h"

#include <Wt/WCssDecorationStyle>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

#include "CWHash.h"
#include "CWOwnerData.h"
#include "Factory.h"

CWOffer::CWOffer ( std::string & strHash, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    CWOwnerData d;
    d.LoadFreeOffers();

    std::map<std::string, CWFreeOffersData>::iterator it;
    it = d.mapFreeOffers.find ( strHash );
    if ( it != d.mapFreeOffers.end() )
    {
        CWFreeOffersData * fod = & ( *it ).second;

        this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/" + fod->strTo + ".jpg" ) );
        this->setStyleClass ( "default-offer-style" );

        this->addWidget ( new Wt::WText ( fod->strFrom ) );
        this->addWidget ( new Wt::WBreak () );
        this->addWidget ( new Wt::WText ( fod->strTo ) );
        this->addWidget ( new Wt::WBreak () );

        Wt::WPushButton * pBtn = new Wt::WPushButton ( fod->strPrice );
        std::string sHash = fod->GetHash();
        pBtn->clicked().connect ( std::bind ( [=]()
        {

        } ) );

//         pBtn->setStyleClass ( p->strBtnStyle );
        this->addWidget ( pBtn );

        Wt::WPushButton * pBtnInstead = new Wt::WPushButton ( fod->strInstead );
//         pBtnInstead->setStyleClass ( p->strBtnInsteadStyle );
        pBtnInstead->setEnabled ( false );
        this->addWidget ( pBtnInstead );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "Can't find offer's hash" ) );
        this->addWidget ( new Wt::WBreak () );
        this->addWidget ( new Wt::WText ( strHash ) );
    }

}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

