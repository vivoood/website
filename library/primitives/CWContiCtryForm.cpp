#include "CWContiCtryForm.h"

#include <Wt/WComboBox>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WText>
#include <Wt/WLineEdit>

#include "Factory.h"
#include "CWCombo.h"

CWContiCtryForm::CWContiCtryForm ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    pContainer = new Wt::WContainerWidget();
    Create ( pD, pContainer, "n/a" );
    this->addWidget ( pContainer );
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

void CWContiCtryForm::Create ( IWidgetData * pD, Wt::WContainerWidget * container, std::string continent )
{
    p = dynamic_cast<WidgetData::SContiCtry*> ( pD );
    if ( p != nullptr )
    {
        std::vector<std::string> conti = this->GetConti();
        Wt::WWidget * w = Factory::CreateComboBox ( "SContiCtryInput", "", conti );
        Format ( w );
        CWCombo * combo = dynamic_cast<CWCombo*> ( w );
        container->addWidget ( combo );

        if ( combo != nullptr )
        {
            if ( continent != "n/a" )
            {
                combo->pEdit->setValueText ( continent );
            }

            combo->pEdit->changed().connect ( std::bind ( [=]()
            {
                std::string strConti = combo->pEdit->currentText().toUTF8();

                container->clear();
                Create ( pD, container, strConti );
            } ) );
        }

        std::vector<std::string> ctry = this->GetCtry ( combo->pEdit->valueText().toUTF8() );
        Wt::WWidget * w2 = Factory::CreateComboBox ( "SContiCtryInput", "", ctry );
        Format ( w2 );
        container->addWidget ( w2 );

        Wt::WLineEdit * line = new Wt::WLineEdit();
        Format ( line );
        container->addWidget ( line );
    }
}

void CWContiCtryForm::Format ( Wt::WWidget* item )
{
    item->setInline ( true );
    item->setMargin ( 10, Wt::Side::Left );
    item->setWidth ( 150 );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 

