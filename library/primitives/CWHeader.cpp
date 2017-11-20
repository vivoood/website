#include "CWHeader.h"

#include <Wt/WTemplate>
#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WCssDecorationStyle>

#include "CWOwnerData.h"

CWHeader::CWHeader ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SHeader * p = dynamic_cast<WidgetData::SHeader*> ( pD );
    if ( p != nullptr )
    {
        Wt::WFont f ( Wt::WFont::SansSerif );
        f.setSize ( "50" );
        f.setWeight ( Wt::WFont::Bold );

        this->setStyleClass ( p->strStyle );
        this->decorationStyle().setBackgroundImage ( Wt::WLink ( "pics/airplane_name_bgr.png" ), Wt::WCssDecorationStyle::NoRepeat, Wt::CenterX );

        CWOwnerData od;
        od.LoadSettings();

        Wt::WText * t = new Wt::WText ( od.settingsData.strTitle );
        t->decorationStyle().setFont ( f );
        t->decorationStyle().setForegroundColor ( Wt::blue );

        f.setSize ( "35" );
        Wt::WText * t2 = new Wt::WText ( od.settingsData.strSlogan );
        t2->decorationStyle().setFont ( f );
        t2->decorationStyle().setForegroundColor ( Wt::yellow );

        this->addWidget ( new Wt::WBreak() );
        this->addWidget ( t );
        this->addWidget ( new Wt::WBreak() );
        this->addWidget ( new Wt::WBreak() );
        this->addWidget ( t2 );
        this->addWidget ( new Wt::WBreak() );
        this->addWidget ( new Wt::WBreak() );

        this->setContentAlignment ( Wt::AlignCenter );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWHeader can't get SHeader from IWidgetData for user: " + pD->strHash ) );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
