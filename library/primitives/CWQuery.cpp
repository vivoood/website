#include "CWQuery.h"

#include <Wt/WDateEdit>
#include <Wt/WCalendar>
#include <Wt/WDate>
#include <Wt/WDateEdit>
#include <Wt/WText>

#include "Factory.h"
#include "CWContiCtryForm.h"

CWQuery::CWQuery ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WWidget * w1 =  Factory::Create ( "CWRadioButtons", "SRadioButtons", "n/a" );
    this->addWidget ( w1 );

    Wt::WWidget * w2 = Factory::Create ( "CWContiCtryForm", "SContiCtry", "n/a" );
    CWContiCtryForm * w21 = dynamic_cast<CWContiCtryForm*> ( w2 );
    w21->SetLabel ( "From: " );
    this->addWidget ( w2 );

    Wt::WWidget * w3 = Factory::Create ( "CWContiCtryForm", "SContiCtry", "n/a" );
    CWContiCtryForm * w31 = dynamic_cast<CWContiCtryForm*> ( w3 );
    w31->SetLabel ( "To: " );
    this->addWidget ( w3 );

    Wt::WText * label = new Wt::WText ( "Choose date of flight " );
    label->setInline ( true );
    this->addWidget ( label );

    Wt::WDateEdit * de1 = new Wt::WDateEdit();
    de1->setDate ( Wt::WDate::currentServerDate() );
    de1->setBottom ( Wt::WDate::currentServerDate() );
    de1->setInline ( true );
    de1->setMargin ( 10, Wt::Side::Left );
    this->addWidget ( de1 );

//     WidgetData::X * p = dynamic_cast<WidgetData::X*> ( pD );
//     if ( p != nullptr )
//     {
// 
//     }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
