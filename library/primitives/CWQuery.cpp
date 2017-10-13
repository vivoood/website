#include "CWQuery.h"

#include <Wt/WDateEdit>
#include <Wt/WCalendar>
#include <Wt/WDate>
#include <Wt/WDateEdit>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>
#include <Wt/WButtonGroup>
#include <Wt/WComboBox>
#include <Wt/WTimer>

#include "Factory.h"
#include "CWContiCtryForm.h"
#include "CWUser.h"
#include "CWRadioButtons.h"

CWQuery::CWQuery ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    container = new Wt::WContainerWidget();
    outmsg = new Wt::WContainerWidget();
    Create ( container, outmsg, pD );
    this->addWidget ( container );
    this->addWidget ( outmsg );
}

void CWQuery::Create ( Wt::WContainerWidget* c, Wt::WContainerWidget * m, IWidgetData * pD )
{
    WidgetData::SQuery * p = dynamic_cast<WidgetData::SQuery*> ( pD );
    if ( p == nullptr )
    {
        this->addWidget ( new Wt::WText ( "CWQuery can't get SQuery from IWidgetData for user: " + pD->strHash ) );
        return;
    }

    Wt::WWidget * w1 =  Factory::Create ( "CWRadioButtons", "SRadioButtons", "n/a" );
    c->addWidget ( w1 );

    Wt::WWidget * w2 = Factory::Create ( "CWContiCtryForm", "SContiCtry", "n/a" );
    CWContiCtryForm * w21 = dynamic_cast<CWContiCtryForm*> ( w2 );
    w21->SetLabel ( "From: " );
    c->addWidget ( w2 );

    c->addWidget ( new Wt::WBreak() );

    Wt::WWidget * w3 = Factory::Create ( "CWContiCtryForm", "SContiCtry", "n/a" );
    CWContiCtryForm * w31 = dynamic_cast<CWContiCtryForm*> ( w3 );
    w31->SetLabel ( "To: " );
    c->addWidget ( w3 );

    c->addWidget ( new Wt::WBreak() );

    Wt::WText * label = new Wt::WText ( "Choose date of flight " );
    label->setInline ( true );
    c->addWidget ( label );

    Wt::WDateEdit * de1 = new Wt::WDateEdit();
    de1->setDate ( Wt::WDate::currentServerDate() );
    de1->setBottom ( Wt::WDate::currentServerDate() );
    de1->setInline ( true );
    de1->setMargin ( 10, Wt::Side::Left );
    c->addWidget ( de1 );

    Wt::WLineEdit * line = new Wt::WLineEdit();
    line->setPlaceholderText ( "Adults..." );
    line->setMargin ( 40, Wt::Side::Left );
    line->setWidth ( 50 );
    c->addWidget ( line );

    Wt::WLineEdit * line2 = new Wt::WLineEdit();
    line2->setPlaceholderText ( "Budget..." );
    line2->setMargin ( 40, Wt::Side::Left );
    line2->setWidth ( 50 );
    c->addWidget ( line2 );

    Wt::WPushButton * btn = new Wt::WPushButton ( "Create this query" );
    btn->setMargin ( 40, Wt::Side::Left );
    c->addWidget ( btn );

    Wt::WTimer * t = new Wt::WTimer ( c );
    t->setInterval ( 3000 );
    t->setSingleShot ( true );
    t->timeout().connect ( std::bind ( [=]()
    {
        m->clear();
        c->clear();
        Create ( c, m, pD );
    } ) );

    btn->clicked().connect ( std::bind ( [=]()
    {
        if ( t->isActive() )
        {
            return;
        }

        CWUser u;
        if ( u.load ( pD->strHash ) )
        {
            CWUser::SAbon ab;
            CWRadioButtons * radio = dynamic_cast<CWRadioButtons*> ( w1 );

            ab._abon = radio->group->checkedId();

            ab._from._conti = w21->continents->currentText().toUTF8();
            ab._from._ctry = w21->country->currentText().toUTF8();
            ab._from._city = w21->city->valueText().toUTF8();

            ab._to._conti = w31->continents->currentText().toUTF8();
            ab._to._ctry = w31->country->currentText().toUTF8();
            ab._to._city = w31->city->valueText().toUTF8();

            ab._date = de1->date().toString().toUTF8();
            ab._adults = line->valueText().toUTF8();
            ab._budget = line2->valueText().toUTF8();

            ab.Normalize();
            
            u.AddAbon ( ab );
            u.save();

            m->addWidget ( new Wt::WText ( "Saved - see all queries on /My Queries/" ) );
            t->start();
        }
        else
        {
            m->addWidget ( new Wt::WText ( "ERROR can't load this user" + pD->strHash ) );
            t->start();
        }
    } ) );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
