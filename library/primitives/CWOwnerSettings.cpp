#include "CWOwnerSettings.h"

#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WCssDecorationStyle>
#include <Wt/WLength>
#include <Wt/WPushButton>
#include <Wt/WBreak>
#include <Wt/WTimer>

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

}

CWOwnerSettings::CWOwnerSettings ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    this->setContentAlignment ( Wt::AlignRight );
    this->setMargin ( Wt::WLength ( 40, Wt::WLength::Percentage ), Wt::Right );

    CWUserLineEdit * t = new CWUserLineEdit ( "Title" );
    this->addWidget ( t );

    CWUserLineEdit * s = new CWUserLineEdit ( "Slogan" );
    this->addWidget ( s );

    Wt::WPushButton * btn = new Wt::WPushButton ( "Save" );
    btn->setMargin ( Wt::WLength ( 1, Wt::WLength::Percentage ) );
    this->addWidget ( btn );

    Wt::WContainerWidget * msg = new Wt::WContainerWidget;
    this->addWidget ( msg );

    btn->clicked().connect ( std::bind ( [=]()
    {
        CWOwnerData d;
        d.settingsData.strTitle = t->pEdit->valueText().toUTF8();
        d.settingsData.strSlogan = s->pEdit->valueText().toUTF8();
        d.SaveSettings();

        t->pEdit->setValueText ( "" );
        s->pEdit->setValueText ( "" );

        msg->clear();
        msg->addWidget ( new Wt::WText ( Wt::WString ( "Title: {1}" ).arg ( d.settingsData.strTitle ) ) );
        msg->addWidget ( new Wt::WBreak() );
        msg->addWidget ( new Wt::WText ( Wt::WString ( "Slogan: {1}" ).arg ( d.settingsData.strSlogan ) ) );
        msg->addWidget ( new Wt::WBreak() );
        msg->addWidget ( new Wt::WText ( Wt::WString ( "Saved successful !!!" ) ) );

        Wt::WTimer * t = new Wt::WTimer ( this );
        t->setInterval ( 5000 );
        t->setSingleShot ( true );
        t->start();
        t->timeout().connect ( std::bind ( [=]()
        {
            msg->clear();
        } ) );

    } ) );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
