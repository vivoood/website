#include "CWContiCtryForm.h"

#include <Wt/WComboBox>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WText>
#include <Wt/WLineEdit>

#include "Factory.h"
#include "CWCombo.h"

int CWContiCtryForm::magic = 0;

CWContiCtryForm::CWContiCtryForm ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    magic++;
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
        Wt::WTable *table = new Wt::WTable();
        table->setWidth ( Wt::WLength ( "100%" ) );
        Wt::WTableCell * pCell = nullptr;

        pCell = table->elementAt ( 0, 0 );

        std::string label = ( ( CWContiCtryForm::magic % 2 == 0 ) ? "To:" : "From:" );
        pCell->addWidget ( new Wt::WText ( label ) );

        std::vector<std::string> conti = this->GetConti();
        Wt::WWidget * w = Factory::CreateComboBox ( "SContiCtryInput", "", conti );
        w->setMargin ( 10, Wt::Side::Left );
        CWCombo * combo = dynamic_cast<CWCombo*> ( w );
        if ( combo != nullptr )
        {
            pCell = table->elementAt ( 0, 1 );
            pCell->addWidget ( combo );

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
        w2->setMargin ( 10, Wt::Side::Left );

        pCell = table->elementAt ( 0, 2 );
        pCell->addWidget ( w2 );

        pCell = table->elementAt ( 0, 3 );
        pCell->addWidget ( new Wt::WLineEdit ( ) );

        container->addWidget ( table );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
