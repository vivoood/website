#include "CWHeader.h"

#include <Wt/WTemplate>
#include <Wt/WText>

CWHeader::CWHeader ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SHeader * p = dynamic_cast<WidgetData::SHeader*> ( pD );
    if ( p != nullptr )
    {
        Wt::WTemplate *templ = new Wt::WTemplate ( Wt::WString::tr ( p->strTemplateName ) );
        templ->bindWidget ( p->strBindName, new Wt::WText ( p->strTitle ) );
        templ->bindWidget ( p->strBindSlogan, new Wt::WText ( p->strSlogan ) );
        this->addWidget ( templ );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWHeader can't get SHeader from IWidgetData for user: " + pD->strHash ) );
    }
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
