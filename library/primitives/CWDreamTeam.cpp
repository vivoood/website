#include "CWDreamTeam.h"

#include <mutex>
#include <iostream>
#include <fstream>

#include <Wt/WComboBox>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WTable>
#include <Wt/WPushButton>
#include <Wt/WCheckBox>
#include <Wt/WTimer>
#include <Wt/WAnchor>
#include <Wt/WLink>

namespace
{

std::vector<std::string> GetNames()
{
    std::vector<std::string> v =
    {
        "Hristo-Staykov",
        "Atanas-Sopotski",
        "Velislav-Velkov",
        "Todor-Kolev",
        "Nikolai-Nedelchev",
        "Dimitar-Dimitrov",
        "Biser-Rangelov",
        "Yordan-Mitarov",
        "Daniel-Milanov",
        "Atanas-Nedelchev",
        "Georgi-Kojuharov",
        "Todor-Spasov",
        "Kiril-Genev",
        "Hristo-Dimitrov",
        "Stanislav-Todorov",
        "Ferai-Ali",
        "Borislav-Dimitrov",
        "Kaloqn-Lozanov",
        "Grigor-Grigorov",
        "Stanislav-Jelev",
        "Galin-Grudov",
        "Pavel-Kehajov",
        "Mladen-Nikolov",
        "Georgi-Faslev",
        "Svetoslav-Trifonov",
        "Safet-Safet",
        "Hristo-Chipilov",
        "Ivo-Genadiev",
        "Ahmed-Karasan",
        "Vladimir-Yanakiev",
        "Nikolai-Ivanov",
        "Todor-Tsonkov",
        "Daniel-Kolev",
    };
    return v;
}

struct user
{
    std::string name;
    std::string date;
    bool admin;
    friend std::ostream& operator<< ( std::ostream& os, const user& dt );
    friend std::istream& operator>> ( std::istream& is, user& dt );
};

std::ostream& operator<< ( std::ostream& os, const user& dt )
{
    os << dt.name << std::endl;
    os << dt.date << std::endl;
    os << dt.admin << std::endl;
    return os;
}

std::istream& operator>> ( std::istream& is, user& dt )
{
    is >> dt.name;
    is >> dt.date;
    is >> dt.admin;
    return is;
}

class users
{
public:
    std::vector<user> v;
    int count = 0;
    void save ()
    {
        std::lock_guard<std::mutex> lock ( mtx );
        std::ofstream outfile ( "owner/dt" );
        count = v.size();
        outfile << count << std::endl;
        for ( auto & i : v )
            outfile << i;
        outfile.close();
    }

    bool load ()
    {
        std::lock_guard<std::mutex> lock ( mtx );
        std::ifstream infile ( "owner/dt" );
        infile >> count;
        for ( int i = 0; i < count; i++ )
        {
            user d;
            infile >> d;
            add ( d );
        }
        infile.close();
    }
    void add ( user d )
    {
        v.push_back ( d );
    }

    std::vector<std::string> getNames ()
    {
        std::vector<std::string> v1;

        for ( auto & i : this->v )
        {
            v1.push_back ( i.name );
        }

        return v1;
    }

private:
    std::mutex mtx;
};

void Update ( Wt::WContainerWidget * p, Wt::WComboBox * c )
{
    p->clear();

    users u;
    u.load();

    Wt::WTable * table = new Wt::WTable();
    table->setWidth ( Wt::WLength ( "20%" ) );

    int cnt = 0;
    int cnt2 = 0;
    for ( unsigned int i = 0; i < u.v.size(); i++ )
    {
        if ( u.v[i].date == "24/11/17" )
            ++cnt;

        if ( u.v[i].date == "01/12/17" )
            ++cnt2;

        Wt::WText * name = new Wt::WText ( u.v[i].name );
        if ( u.v[i].admin )
            name->decorationStyle().setForegroundColor ( Wt::red );

        if ( u.v[i].date == "nqma_da_doida" )
            name->decorationStyle().setForegroundColor ( Wt::gray );

        table->elementAt ( i, 0 )->addWidget ( name );
        table->elementAt ( i, 0 )->setContentAlignment ( Wt::AlignCenter );

        Wt::WText * tnqma = new Wt::WText ( u.v[i].date );
        if ( u.v[i].date == "nqma_da_doida" )
        {
            tnqma->setText ( "" );
            tnqma->decorationStyle().setForegroundColor ( Wt::gray );
        }

        if ( u.v[i].admin )
        {
            tnqma->decorationStyle().setForegroundColor ( Wt::red );
        }

        table->elementAt ( i, 1 )->addWidget ( tnqma );
        table->elementAt ( i, 1 )->setContentAlignment ( Wt::AlignCenter );
    }

    Wt::WText * txt = new Wt::WText ( Wt::WString ( "izbrana data {1}/{2}" ).arg ( std::max ( cnt,cnt2 ) ).arg ( std::min ( cnt,cnt2 ) ) );
    txt->decorationStyle().setForegroundColor ( Wt::blue );

    Wt::WText * txt2 = new Wt::WText ( "" );
    txt2->decorationStyle().setForegroundColor ( Wt::blue );

    table->elementAt ( u.v.size(), 0 )->addWidget ( txt );
    table->elementAt ( u.v.size(), 0 )->setContentAlignment ( Wt::AlignCenter );

    if ( cnt == cnt2 )
    {
        txt2->setText ( "50/50" );
        txt2->decorationStyle().setForegroundColor ( Wt::magenta );
    }
    else if ( cnt > cnt2 )
        txt2->setText ( "24/11/17" );
    else
        txt2->setText ( "01/12/17" );

    table->elementAt ( u.v.size(), 1 )->addWidget ( txt2 );
    table->elementAt ( u.v.size(), 1 )->setContentAlignment ( Wt::AlignCenter );

    p->addWidget ( new Wt::WBreak() );
    p->addWidget ( new Wt::WBreak() );
    p->addWidget ( table );
}

}

CWDreamTeam::CWDreamTeam ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WContainerWidget * tit = new Wt::WContainerWidget();

    Wt::WFont font ( Wt::WFont::SansSerif );
    font.setSize ( "30" );
    font.setWeight ( Wt::WFont::Bold );

    Wt::WAnchor * pAnchor = new Wt::WAnchor ( Wt::WLink ( "https://www.borovetz-resort.com/vilno-selishte-malina/" ), Wt::WString ( "Koito iska da hodim na malina, qgoda, sliva i t.n." ) );
    tit->addWidget ( pAnchor );
    tit->decorationStyle().setFont ( font );

    this->addWidget ( tit );

    Wt::WContainerWidget * list = new Wt::WContainerWidget();

    Wt::WContainerWidget * err = new Wt::WContainerWidget();
    err->hide();

    Wt::WTable * table = new Wt::WTable();
    table->setHeaderCount ( 1 );
    table->setWidth ( Wt::WLength ( "40%" ) );



    std::vector<std::string> v1 = GetNames();

    users mu;
    mu.load();
    std::vector<std::string> v2 = mu.getNames();

    for ( int i = 0; i < v2.size(); i++ )
    {
        std::string idt = v2[i];
        std::vector<std::string>::iterator it;
        it = std::find ( v1.begin(), v1.end(), idt );
        if ( it != v1.end() )
        {
            v1.erase ( it );
        }
    }



    sort ( v1.begin(),v1.end() );
    Wt::WComboBox * pEdit = new Wt::WComboBox();
    for ( auto it : v1 )
        pEdit->addItem ( it );

    Update ( list, pEdit );

    Wt::WComboBox * pEditDate = new Wt::WComboBox();
    pEditDate->addItem ( "24/11/17" );
    pEditDate->addItem ( "01/12/17" );
    pEditDate->addItem ( "bez_zna4enie" );
    pEditDate->addItem ( "nqma_da_doida" );

    Wt::WCheckBox * cbox = new Wt::WCheckBox();
    Wt::WPushButton * btn = new Wt::WPushButton ( "Add me" );
    Wt::WPushButton * btn2 = new Wt::WPushButton ( "Update" );

    table->elementAt ( 0, 0 )->addWidget ( new Wt::WText ( "Ime" ) );
    table->elementAt ( 0, 0 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 1, 0 )->addWidget ( pEdit );
    table->elementAt ( 1, 0 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 0, 1 )->addWidget ( new Wt::WText ( "Data" ) );
    table->elementAt ( 0, 1 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 1, 1 )->addWidget ( pEditDate );
    table->elementAt ( 1, 1 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 0, 2 )->addWidget ( new Wt::WText ( "Iskam da sym organizator" ) );
    table->elementAt ( 0, 2 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 1, 2 )->addWidget ( cbox );
    table->elementAt ( 1, 2 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 0, 3 )->addWidget ( new Wt::WText ( "" ) );
    table->elementAt ( 0, 3 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 1, 3 )->addWidget ( btn );
    table->elementAt ( 1, 3 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 0, 4 )->addWidget ( new Wt::WText ( "" ) );
    table->elementAt ( 0, 4 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 1, 4 )->addWidget ( btn2 );
    table->elementAt ( 1, 4 )->setContentAlignment ( Wt::AlignCenter );

    table->elementAt ( 2, 0 )->addWidget ( err );
    table->elementAt ( 2, 0 )->setContentAlignment ( Wt::AlignCenter );

    this->addWidget ( table );
    this->addWidget ( list );

    btn->clicked().connect ( std::bind ( [=]()
    {
        user u1;
        u1.name = pEdit->currentText().toUTF8();
        u1.date = pEditDate->currentText().toUTF8();
        u1.admin = cbox->isChecked();

        users u;
        u.load();

        for ( auto & i : u.v )
        {
            if ( i.name == u1.name )
            {
                if ( err->count() == 0 )
                {
                    err->show();

                    Wt::WFont fnt ( Wt::WFont::SansSerif );
                    fnt.setSize ( "11" );
                    fnt.setWeight ( Wt::WFont::Bold );

                    Wt::WText * txt = new Wt::WText ( Wt::WString ( "Imeto e izpolzvano" ) );
                    txt->decorationStyle().setForegroundColor ( Wt::red );
                    txt->decorationStyle().setFont ( fnt );
                    err->addWidget ( txt );

                    Wt::WTimer * t = new Wt::WTimer ( this );
                    t->setInterval ( 5000 );
                    t->setSingleShot ( true );
                    t->start();
                    t->timeout().connect ( std::bind ( [=]()
                    {
                        err->hide();
                        err->clear();
                    } ) );
                }
                return;
            }
        }

        u.add ( u1 );
        u.save();

        Update ( list, pEdit );

    } ) );

    btn2->clicked().connect ( std::bind ( [=]()
    {
        Update ( list, pEdit );
    } ) );

}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
