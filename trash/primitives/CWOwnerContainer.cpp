#include "CWOwnerContainer.h"

#include <Wt/WLineEdit>
#include <Wt/WMenu>
#include <Wt/WMessageBox>
#include <Wt/WNavigationBar>
#include <Wt/WPopupMenu>
#include <Wt/WPopupMenuItem>
#include <Wt/WStackedWidget>
#include <Wt/WText>

#include "Factory.h"

CWOwnerContainer::CWOwnerContainer ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
//     this->addWidget ( Factory::Create ( "CWOwnerFreeOffers", "SOwnerFreeOffers", "owner" ) );
//     this->addWidget ( Factory::Create ( "CWOwnerFreeOffersView", "SOwnerFreeOffers", "owner" ) );


    Wt::WContainerWidget * container = new Wt::WContainerWidget();

    Wt::WNavigationBar *navigation = new Wt::WNavigationBar();
    container->addWidget ( navigation );
    navigation->setTitle ( "Corpy Inc.", "http://www.google.com/search?q=corpy+inc" );
    navigation->setResponsive ( true );

    Wt::WStackedWidget *contentsStack = new Wt::WStackedWidget();
    container->addWidget ( contentsStack );
    contentsStack->addStyleClass ( "contents" );

    Wt::WMenu * leftMenu = new Wt::WMenu ( contentsStack );
    navigation->addMenu ( leftMenu );

    Wt::WText * searchResult = new Wt::WText ( "Buy or Sell... Bye!" );

    leftMenu->addItem ( "Home", new Wt::WText ( "There is no better place!" ) );
    leftMenu->addItem ( "Layout", new Wt::WText ( "Layout contents" ) ) /*->setLink ( Wt::WLink ( Wt::LinkType::InternalPath, "/layout" ) )*/;
    leftMenu->addItem ( "Sales", searchResult );

    Wt::WMenu * rightMenu = new Wt::WMenu();
    navigation->addMenu ( rightMenu );

    Wt::WPopupMenu * popupPtr = new Wt::WPopupMenu();
    popupPtr->addItem ( "Contents" );
    popupPtr->addItem ( "Index" );
    popupPtr->addSeparator();
    popupPtr->addItem ( "About" );

//     popupPtr->itemSelected().connect ( std::bind ( [=] ( Wt::WMenuItem *item )
//     {
//         Wt::WMessageBox * messageBox = new Wt::WMessageBox ( "Help",Wt::WString ( "<p>Showing Help: {1}</p>" ).arg ( item->text() ),Wt::Icon::Information, Wt::StandardButton::Ok );
//         messageBox->show();
//     } ) );

    Wt::WMenuItem * item = new Wt::WMenuItem ( "Help" );
    item->setMenu ( std::move ( popupPtr ) );
    rightMenu->addItem ( std::move ( item ) );

// Add a Search control.
    Wt::WLineEdit * editPtr = new Wt::WLineEdit();
    editPtr->setPlaceholderText ( "Enter a search item" );

    editPtr->enterPressed().connect ( std::bind ( [=]
    {
        leftMenu->select ( 2 ); // is the index of the "Sales"
        searchResult->setText ( Wt::WString ( "Nothing found for {1}." )
        .arg ( editPtr->text() ) );
    } ) );

    navigation->addSearch ( std::move ( editPtr ) );

    this->addWidget ( navigation );

}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
