#include "CWOwnerFreeOffers.h"

#include <sstream>

#include <Wt/WText>
#include <Wt/WTable>
#include <Wt/WLineEdit>
#include <Wt/WCheckBox>
#include <Wt/WPushButton>
#include <Wt/WBreak>
#include <Wt/WIntValidator>
#include <Wt/WAnimation>
#include <Wt/WTimer>

#include "Factory.h"
#include "CWOwnerData.h"

namespace
{

void SetIntValidator ( unsigned int i, Wt::WWidget * w )
{
    if ( i == static_cast<int> ( OwnerEID::price ) || i == static_cast<int> ( OwnerEID::instead ) )
    {
        Wt::WLineEdit * edit = dynamic_cast<Wt::WLineEdit *> ( w );
        if ( nullptr != edit )
            edit->setValidator ( new Wt::WIntValidator );
    }
}

void GetValueFromLineEdit ( Wt::WTable * t, OwnerEID e, int & val )
{
    Wt::WTableCell * pCell = t->elementAt ( static_cast<int> ( e ), 1 );
    Wt::WWidget * w = pCell->widget ( 0 );
    Wt::WLineEdit * edit = dynamic_cast<Wt::WLineEdit *> ( w );

    std::stringstream ss;
    std::string str = edit->text().toUTF8();
    ss << str;

    val = 0;
    ss >> val;
}

void GetValueFromLineEdit ( Wt::WTable * t, OwnerEID e, std::string & val, bool clear = false )
{
    Wt::WTableCell * pCell = t->elementAt ( static_cast<int> ( e ), 1 );
    Wt::WWidget * w = pCell->widget ( 0 );
    Wt::WLineEdit * edit = dynamic_cast<Wt::WLineEdit *> ( w );

    val = edit->text().toUTF8();

    if ( clear )
        edit->setText ( "" );
}

void GetValueFromCheckBox ( Wt::WTable * t, OwnerEID e, bool & val, bool clear = false )
{
    Wt::WTableCell * pCell = t->elementAt ( static_cast<int> ( e ), 1 );
    Wt::WWidget * w = pCell->widget ( 0 );
    Wt::WCheckBox * check = dynamic_cast<Wt::WCheckBox *> ( w );

    val = check->isChecked();

    if ( clear )
        check->setCheckState ( Wt::Unchecked );
}

}

CWOwnerFreeOffers::CWOwnerFreeOffers ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SOwnerFreeOffers * p = dynamic_cast<WidgetData::SOwnerFreeOffers*> ( pD );
    if ( p != nullptr )
    {
        this->setContentAlignment ( Wt::AlignCenter );

        Wt::WTable * table = new Wt::WTable();
        table->setWidth ( Wt::WLength ( "100%" ) );

        Wt::WTableCell * pCell = nullptr;

        for ( unsigned int i = 0; i < p->v.size(); i++ )
        {
            pCell = table->elementAt ( i, 0 );
            pCell->addWidget ( new Wt::WText ( p->v[i].label ) );

            Wt::WWidget * w = Factory::Create ( p->v[i].widget, "", "" );
            SetIntValidator ( i, w );

            pCell = table->elementAt ( i, 1 );
            pCell->addWidget ( w );
        }

        this->addWidget ( table );

        Wt::WPushButton * btn = new Wt::WPushButton ( "Ready to add data" );
        this->addWidget ( btn );

        Wt::WContainerWidget * pErr = new Wt::WContainerWidget();
        pErr->hide();
        this->addWidget ( pErr );

        btn->clicked().connect ( std::bind ( [=]()
        {
            pErr->clear();

            int pr = 0;
            GetValueFromLineEdit ( table, OwnerEID::price, pr );
            int ins = 0;
            GetValueFromLineEdit ( table, OwnerEID::instead, ins );
            if ( pr >= ins )
            {
                pErr->addWidget ( new Wt::WBreak() );
                pErr->addWidget ( new Wt::WText ( Wt::WString ( "Error: Price = {1} must be more than instead = {2}" ).arg ( pr ).arg ( ins ) ) );
            }

            std::vector<OwnerEID> vec = { OwnerEID::from, OwnerEID::to, OwnerEID::airl, OwnerEID::link };
            for ( unsigned int i = 0; i < vec.size(); i++ )
            {
                std::string val;
                GetValueFromLineEdit ( table, vec[i], val );
                if ( val.empty() )
                {
                    pErr->addWidget ( new Wt::WBreak() );
                    pErr->addWidget ( new Wt::WText ( Wt::WString ( "Error: {1} can't be empty" ).arg ( p->Find ( vec[i] ) ) ) );
                }
            }

            if ( pErr->count() > 0 )
            {
                pErr->show();
                Wt::WTimer * t = new Wt::WTimer ( this );
                t->setInterval ( 5000 );
                t->setSingleShot ( true );
                t->start();
                t->timeout().connect ( std::bind ( [=]()
                {
                    pErr->hide();
                    pErr->clear();
                } ) );
            }
            else
            {
                CWFreeOffersData d;
                GetValueFromLineEdit ( table, OwnerEID::from, d.strFrom, true );
                GetValueFromLineEdit ( table, OwnerEID::to, d.strTo, true );
                GetValueFromLineEdit ( table, OwnerEID::airl, d.strAirline, true );
                GetValueFromLineEdit ( table, OwnerEID::price, d.strPrice, true );
                GetValueFromLineEdit ( table, OwnerEID::instead, d.strInstead, true );
                GetValueFromCheckBox ( table, OwnerEID::oneway, d.bOneWay, true );
                GetValueFromCheckBox ( table, OwnerEID::direct, d.bDirectFlight, true );
                GetValueFromLineEdit ( table, OwnerEID::link, d.strHyperlink, true );

                CWOwnerData owner;
                owner.LoadFreeOffers();
                owner.AddFreeOffer ( d );
                owner.SaveFreeOffers();
            }

        } ) );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWOwnerFreeOffers can't get SOwnerFreeOffers from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

