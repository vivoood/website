#include "CWContiCtryForm.h"

#include <Wt/WComboBox>

#include "Factory.h"
#include "CWCombo.h"

CWContiCtryForm::CWContiCtryForm ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    p = dynamic_cast<WidgetData::SContiCtry*> ( pD );
    if ( p != nullptr )
    {
        Wt::WWidget * w = Factory::CreateComboBox ( "SContiCtryInput", "", this->GetConti() );
        this->addWidget ( w );

        CWCombo * combo = dynamic_cast<CWCombo*> ( w );
        std::string str;
        if ( combo != nullptr )
            str = combo->pEdit->currentText().toUTF8();

        Wt::WWidget * w2 = Factory::CreateComboBox ( "SContiCtryInput", "", this->GetCtry ( str ) );
        this->addWidget ( w2 );

        combo->pEdit->changed().connect ( std::bind ( [=]()
        {
            std::string strV = combo->pEdit->currentText().toUTF8();
        } ) );
    }
}

std::vector<std::string> CWContiCtryForm::GetConti ()
{
    std::vector< std::string > c;
    if ( p != nullptr )
    {
        for ( const auto &it : p->_list )
        {
            c.push_back ( it.first );
        }
    }

    return c;
}

std::vector<std::string> CWContiCtryForm::GetCtry ( std::string str )
{
    std::vector< std::string > c;
    if ( p != nullptr )
    {
        std::map< std::string, std::vector< std::string > >::iterator it = p->_list.find ( str );
        if ( it != p->_list.end() )
        {
            c = ( *it ).second;
        }
    }

    return c;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


