#include "CWLineEditField.h"

#include <Wt/WText>
#include <Wt/WLineEdit>

CWLineEditField::CWLineEditField ( std::string label, Wt::WContainerWidget* parent ) : WContainerWidget ( nullptr )
{
    if ( parent == nullptr )
    {
        this->addWidget ( new Wt::WText ( "parent == nullptr" ) );
        return;
    }

    parent->setContentAlignment ( Wt::AlignRight );

    this->addWidget ( new Wt::WText ( label ) );
    pEdit = new Wt::WLineEdit();
    this->addWidget ( pEdit );
}

std::string CWLineEditField::Value()
{
    return pEdit->text().toUTF8();
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
