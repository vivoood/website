#include "CWOwnerSettings.h"

#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WCssDecorationStyle>
#include <Wt/WLength>
#include <Wt/WPushButton>
#include <Wt/WBreak>
#include <Wt/WTimer>
#include <Wt/WIntValidator>

#include "CWOwnerData.h"

namespace
{

class CWUserLineEdit : public Wt::WContainerWidget
{
public:
    CWUserLineEdit ( std::string txt )
    {
        pText = new Wt::WText ( txt );
        pText->setMargin ( Wt::WLength ( 1, Wt::WLength::Percentage ) );
        this->addWidget ( pText );
        pEdit = new Wt::WLineEdit();
        pEdit->setMargin ( Wt::WLength ( 1, Wt::WLength::Percentage ) );
        pEdit->setWidth ( "200" );
        this->addWidget ( pEdit );
    }

    Wt::WText * pText = nullptr;
    Wt::WLineEdit * pEdit = nullptr;
};

void UpdateAbCount()
{
}

void ShowMsg ( std::vector<std::string> & txt, Wt::WContainerWidget * pContainer, Wt::WTimer * t )
{
    pContainer->clear();

    for ( auto & i : txt )
    {
        pContainer->addWidget ( new Wt::WText ( i ) );
        pContainer->addWidget ( new Wt::WBreak() );
    }

    t->setInterval ( 5000 );
    t->setSingleShot ( true );
    t->start();
    t->timeout().connect ( std::bind ( [=]()
    {
        pContainer->clear();
    } ) );
}

void AddAbonaments ( Wt::WContainerWidget * p, int counter )
{
    p->clear();
    for ( int i = 0; i < counter; i++ )
    {
        p->addWidget ( new Wt::WText ( "asdasdswd" ) );
        p->addWidget ( new Wt::WBreak() );
    }
}

}

CWOwnerSettings::CWOwnerSettings ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WTimer * timer = new Wt::WTimer ( this );

    this->setContentAlignment ( Wt::AlignRight );
    this->setMargin ( Wt::WLength ( 40, Wt::WLength::Percentage ), Wt::Right );

    CWUserLineEdit * t = new CWUserLineEdit ( "Title" );
    this->addWidget ( t );

    CWUserLineEdit * s = new CWUserLineEdit ( "Slogan" );
    this->addWidget ( s );

//     CWUserLineEdit * abcnt = new CWUserLineEdit ( "Abonaments" );
//     abcnt->pEdit->setValidator ( new Wt::WIntValidator() );

//     Wt::WPushButton * btnAb = new Wt::WPushButton ( "Push" );
//     btnAb->setMargin ( Wt::WLength ( 1, Wt::WLength::Percentage ) );
//     abcnt->addWidget ( btnAb );

//     Wt::WContainerWidget * content = new Wt::WContainerWidget();
//     abcnt->addWidget ( new Wt::WBreak() );
//     abcnt->addWidget ( content );
//     AddAbonaments ( content, 0 );

//     this->addWidget ( abcnt );

    Wt::WPushButton * btn = new Wt::WPushButton ( "Save" );
    btn->setMargin ( Wt::WLength ( 1, Wt::WLength::Percentage ) );
    this->addWidget ( btn );

    Wt::WContainerWidget * msg = new Wt::WContainerWidget;
    this->addWidget ( msg );

    btn->clicked().connect ( std::bind ( [=]()
    {
        if ( timer->isActive() )
            return;

        CWOwnerData d;
        d.settingsData.strTitle = t->pEdit->valueText().toUTF8();
        d.settingsData.strSlogan = s->pEdit->valueText().toUTF8();
        d.SaveSettings();

        t->pEdit->setValueText ( "" );
        s->pEdit->setValueText ( "" );

        std::vector<std::string> txt;
        txt.push_back ( Wt::WString ( "Title: {1}" ).arg ( d.settingsData.strTitle ).toUTF8() );
        txt.push_back ( Wt::WString ( "Slogan: {1}" ).arg ( d.settingsData.strSlogan ).toUTF8() );
        txt.push_back ( Wt::WString ( "Saved successful !!!" ).toUTF8() );
        ShowMsg ( txt, msg, timer );

    } ) );

//     btnAb->clicked().connect ( std::bind ( [=]()
//     {
//         if ( timer->isActive() )
//             return;
// 
//         CWOwnerData d;
//         d.LoadSettings();
// 
//         int val = 0;
// 
//         std::stringstream ss;
//         ss << abcnt->pEdit->valueText();
//         ss >> val;
// 
//         d.settingsData.nAbonamenstCount = val;
// 
//         if ( ( val > 0 ) && ( val < 7 ) )
//         {
//             AddAbonaments ( content, val );
//         }
//         else
//         {
//             std::vector<std::string> txt;
//             txt.push_back ( "Abonaments must between 1 and 6" );
//             ShowMsg ( txt, msg, timer );
//         }
//     } ) );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

