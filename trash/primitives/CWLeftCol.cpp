#include "CWLeftCol.h"

#include <Wt/WText>

#include "Factory.h"

CWLeftCol::CWLeftCol ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SLeftCol * p = dynamic_cast<WidgetData::SLeftCol*> ( pD );
    if ( p != nullptr )
    {
        for ( auto const& x : p->m_vWidgets )
        {
            this->addWidget ( Factory::Create ( x.first, x.second, p->strHash ) );
        }
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWLeftCol can't get SLeftCol from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
