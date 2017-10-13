#include "CWContacts.h"

#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WBreak>
#include <Wt/WTextArea>
#include <Wt/WPushButton>

CWContacts::CWContacts ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
//     WidgetData::STabButtonsContentData * p = dynamic_cast<WidgetData::STabButtonsContentData*> ( pD );
//     if ( p != nullptr )
    {
//         this->setStyleClass ( p->strWidgetStyle );

        Wt::WContainerWidget * pLabelsContainer = new Wt::WContainerWidget();

        Wt::WText * pEmailLabel = new Wt::WText ( "Your e-mail" );
        pLabelsContainer->addWidget ( pEmailLabel );

        Wt::WLineEdit * pEmailEdit = new Wt::WLineEdit ( );
        pLabelsContainer->addWidget ( pEmailEdit );

        pLabelsContainer->addWidget ( new Wt::WBreak() );

        Wt::WText * pSubjectLabel = new Wt::WText ( "Subject" );
        pLabelsContainer->addWidget ( pSubjectLabel );

        Wt::WLineEdit * pSubjectEdit = new Wt::WLineEdit ( );
        pLabelsContainer->addWidget ( pSubjectEdit );

        pLabelsContainer->setStyleClass ( "email-labels" );
        this->addWidget ( pLabelsContainer );

        Wt::WContainerWidget * pTextContainer = new Wt::WContainerWidget();

        Wt::WTextArea * pMsgEdit = new Wt::WTextArea ();
        pMsgEdit->setToolTip ( "Enter text for e-mail" );
        pMsgEdit->unsetDraggable();
        pTextContainer->setStyleClass ( "email-text" );
        pTextContainer->addWidget ( pMsgEdit );

        pTextContainer->addWidget ( new Wt::WBreak() );

        pTextContainer->addWidget ( new Wt::WPushButton ( "Send" ) );

        this->addWidget ( pTextContainer );

    }
//     else
//     {
//         this->addWidget ( new Wt::WText ( "CWContacts can't get STabButtonsContentData from IWidgetData for user: " + pD->strHash ) );
//     }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
