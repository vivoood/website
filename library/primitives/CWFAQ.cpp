#include "CWFAQ.h"

#include <Wt/WText>

CWFAQ::CWFAQ ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::STabButtonsContentData * p = dynamic_cast<WidgetData::STabButtonsContentData*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strWidgetStyle );

        this->addWidget ( new Wt::WText ( "<h2>- How do I choose the right airline?</h2>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Low-cost airlines: The cheapest option but eliminate many of the standard flight benefits such as meals and complimentary drinks</cite></p>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Charter airlines: Offer flights outside normal schedules and operate on behalf of travel companies</cite></p>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Scheduled flights: Work through the airline itself or travel agents and operate to published schedules</cite></p>" ) );

        this->addWidget ( new Wt::WText ( "<h2>- What are the main ticket options?</h2>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Standard economy</cite></p>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Premium economy</cite></p>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Business class</cite></p>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>First class</cite></p>" ) );

        this->addWidget ( new Wt::WText ( "<h2>- When do flight prices change?</h2>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>An airline will typically charge between five and 15 different prices for the same seat over the course of its shelf life.</cite></p>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Advance prices will be lower, and as the flight fills up prices will increase. However, as the departure date looms airlines are likely to drop their prices dramatically in order to fill space</cite></p>" ) );

        this->addWidget ( new Wt::WText ( "<h2>- What time of day is it cheapest to fly?</h2>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Flying late at night or very early morning will often mean routes are less crowded, but this can mean extended airport stays or arriving after or before hotel check-in.</cite></p>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Airlines need to maintain a schedule during off peak times - try to make your weekend trip happen during the week and you may get a cheaper and quieter flight.</cite></p>" ) );

        this->addWidget ( new Wt::WText ( "<h2>- Are indirect flights cheaper?</h2>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>It's possible that taking indirect routes and making long stopovers will reduce airfares. The downside, however, is that the extra time spent on the plane or in an airport might reduce the length of your holiday.</cite></p>" ) );

        this->addWidget ( new Wt::WText ( "<h2>- Who pays if I miss a connecting flight?</h2>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>If you're travelling on a 'through' ticket and your connection is missed, the airline is obliged to source a seat on the next available flight and pay for expenses and overnight accommodation.</cite></p>" ) );

        this->addWidget ( new Wt::WText ( "<h2>- Should I pay by credit card?</h2>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>Credit cards provide you with additional cover should the airline go bust under the Consumer Credit Act, but remember that you may be charged interest if you don't pay off the balance in full at the end of the month.</cite></p>" ) );

        this->addWidget ( new Wt::WText ( "<h2>- What other protection might I have?</h2>" ) );
        this->addWidget ( new Wt::WText ( "<p><cite>It's always worth thinking about good travel insurance cover before booking a flight, and you may want to consider whether your policy has scheduled airline failure insurance (Safi) included.</cite></p>" ) );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWFAQ can't get STabButtonsContentData from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
