#include "CWOfferBig.h"

#include <Wt/WAnchor>
#include <Wt/WLink>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WTable>
#include <Wt/WPushButton>
#include <Wt/WCssDecorationStyle>

CWOfferBig::CWOfferBig ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOffer * p = dynamic_cast<WidgetData::SOffer*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->offerBig.strStyle );
//         this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/" + p->offerBig.strTo + ".jpg" ), Wt::WCssDecorationStyle::NoRepeat, Wt::CenterX );

        Wt::WContainerWidget * pContainer = new Wt::WContainerWidget();
        pContainer->setContentAlignment ( Wt::AlignCenter );
        pContainer->addWidget ( new Wt::WText ( "You can take low cost holiday to" ) );
        pContainer->addWidget ( new Wt::WBreak() );
        pContainer->addWidget ( new Wt::WText ( p->offerBig.strTo ) );
        pContainer->addWidget ( new Wt::WBreak() );
        pContainer->addWidget ( new Wt::WText ( "air travel will cost only " + p->offerBig.strPrice + " instead " + p->offerBig.strInstead ) );
        pContainer->addWidget ( new Wt::WBreak() );
        std::string btnName = "Show details";
        Wt::WPushButton * btn = new Wt::WPushButton ( btnName );
        pContainer->addWidget ( btn );
        this->addWidget ( pContainer );

        Wt::WContainerWidget * pContainer2 = new Wt::WContainerWidget();
        pContainer2->hide();

        Wt::WTable *table = new Wt::WTable();
        table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Price" ) );
        table->elementAt ( 0, 1 )->addWidget ( new Wt::WText ( p->offerBig.strPrice ) );
        table->elementAt ( 1, 0 )->addWidget ( new Wt::WText ( "Airline" ) );
        table->elementAt ( 1, 1 )->addWidget ( new Wt::WText ( p->offerBig.strAirline ) );
        table->elementAt ( 2, 0 )->addWidget ( new Wt::WText ( "Way" ) );
        table->elementAt ( 2, 1 )->addWidget ( new Wt::WText ( p->offerBig.bOneWay ? "one" : "two" ) );
        table->elementAt ( 3, 0 )->addWidget ( new Wt::WText ( "Direct" ) );
        table->elementAt ( 3, 1 )->addWidget ( new Wt::WText ( p->offerBig.bDirectFlight ? "yes" : "no" ) );
        table->elementAt ( 4, 0 )->addWidget ( new Wt::WText ( "Website" ) );
        table->elementAt ( 4, 1 )->addWidget ( new Wt::WAnchor ( Wt::WLink ( p->offerBig.strHyperlink ), "link" ) );

        pContainer2->addWidget ( table );
        this->addWidget ( pContainer2 );

        btn->clicked().connect ( std::bind ( [=]()
        {
            std::string t = btn->text().toUTF8();
            if ( t == btnName )
            {
                btn->setText ( "Hide" );
                pContainer2->show();
            }
            else
            {
                btn->setText ( btnName );
                pContainer2->hide();
            }

        } ) );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWOfferBig can't get SOffer from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
