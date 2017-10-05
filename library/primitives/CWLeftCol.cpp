#include "CWLeftCol.h"

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
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
