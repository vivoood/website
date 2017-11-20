#include "CWOffer.h"

#include <Wt/WCssDecorationStyle>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

#include "CWSignals.h"
#include "CWHash.h"
#include "CWOwnerData.h"
#include "Factory.h"

CWOffer::CWOffer ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffer * p = dynamic_cast<WidgetData::SOffer*> ( pD );
    if ( p != nullptr )
    {
        CWOwnerData d;
        d.LoadFreeOffers();

        std::map<std::string, CWFreeOffersData>::iterator it;
        it = d.mapFreeOffers.find ( p->strHash );
        if ( it != d.mapFreeOffers.end() )
        {
            CWFreeOffersData * fod = & ( *it ).second;

            this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/" + fod->strTo + ".jpg" ) );
            this->setStyleClass ( p->strStyle );

            this->addWidget ( new Wt::WText ( fod->strFrom ) );
            this->addWidget ( new Wt::WBreak () );
            this->addWidget ( new Wt::WText ( fod->strTo ) );
            this->addWidget ( new Wt::WBreak () );

            Wt::WPushButton * pBtn = new Wt::WPushButton ( fod->strPrice );
            std::string sHash = fod->GetHash();
            pBtn->clicked().connect ( std::bind ( [=]()
            {
                gCWSignals.signaloffertotab.emit ( "CWOfferBig", "SOffer", sHash );
            } ) );

            pBtn->setStyleClass ( p->strBtnStyle );
            this->addWidget ( pBtn );
        }
        else
        {
            this->addWidget ( new Wt::WText ( "Can't find offer's hash" ) );
            this->addWidget ( new Wt::WBreak () );
            this->addWidget ( new Wt::WText ( p->strHash ) );
        }
    }
    else
    {
        if ( nullptr == pD )
            this->addWidget ( new Wt::WText ( "CWOffer pD is nullptr " ) );
        else
            this->addWidget ( new Wt::WText ( "CWOffer can't get SOffer from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

