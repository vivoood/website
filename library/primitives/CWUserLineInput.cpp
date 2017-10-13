#include "CWUserLineInput.h"

#include <Wt/WText>
#include <Wt/WLineEdit>

CWUserLineInput::CWUserLineInput ( IWidgetData * pD, std::stringstream &ss, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SUserInput * p = dynamic_cast<WidgetData::SUserInput*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyleContainer );

        std::string str;
        ss >> str;

        std::replace ( str.begin(), str.end(), '_', ' ' );

        pText = new Wt::WText ( str );
        pText->setStyleClass ( p->strStyleLabel );
        this->addWidget ( pText );

        pEdit = new Wt::WLineEdit ( );
        pEdit->setStyleClass ( p->strStyleLineEdit );
        this->addWidget ( pEdit );
    }
    else
    {
        this->addWidget ( new Wt::WText ( "CWUserLineInput can't get SUserInput from IWidgetData for user: " + pD->strHash ) );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
