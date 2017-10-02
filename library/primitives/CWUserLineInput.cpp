#include "CWUserLineInput.h"

#include <Wt/WText>
#include <Wt/WLineEdit>

CWUserLineInput::CWUserLineInput ( IWidgetData* pD, Wt::WContainerWidget* parent )
{
    WidgetData::SUserLineInput * p = dynamic_cast<WidgetData::SUserLineInput*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyleContainer );

        Wt::WText * pLabel = new Wt::WText ( "default" );
        pLabel->setStyleClass ( p->strStyleLabel );
        this->addWidget ( pLabel );

        Wt::WLineEdit * pEdit = new Wt::WLineEdit ( );
        pEdit->setStyleClass ( p->strStyleLineEdit );
        this->addWidget ( pEdit );
    }
}

CWUserLineInput::CWUserLineInput ( IWidgetData * pD, std::stringstream &ss, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    WidgetData::SUserLineInput * p = dynamic_cast<WidgetData::SUserLineInput*> ( pD );
    if ( p != nullptr )
    {
        this->setStyleClass ( p->strStyleContainer );

        std::string str;
        ss >> str;

        std::replace ( str.begin(), str.end(), '_', ' ' );

        Wt::WText * pLabel = new Wt::WText ( str );
        pLabel->setStyleClass ( p->strStyleLabel );
        this->addWidget ( pLabel );

        Wt::WLineEdit * pEdit = new Wt::WLineEdit ( );
        pEdit->setStyleClass ( p->strStyleLineEdit );
        this->addWidget ( pEdit );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
