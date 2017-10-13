#include "CWCombo.h"

#include <Wt/WText>
#include <Wt/WComboBox>

CWCombo::CWCombo ( IWidgetData * pD, const std::string & label, const std::vector<std::string> & values, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SUserInput * p = dynamic_cast<WidgetData::SUserInput*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyleContainer );

        pText = new Wt::WText ( label );
        pText->setStyleClass ( p->strStyleLabel );
        this->addWidget ( pText );

        pEdit = new Wt::WComboBox();
        for ( auto it : values )
            pEdit->addItem ( it );
        pEdit->setStyleClass ( p->strStyleLineEdit );

        this->addWidget ( pEdit );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWCombo can't get SUserInput from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
