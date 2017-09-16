#include "WTabs.h"

#include <Wt/WTemplate>
#include <Wt/WPushButton>

WTabs::WTabs ( Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    Wt::WTemplate * templ = new Wt::WTemplate ( Wt::WString::tr ( "web-site-menu-template" ) );
    
    Wt::WPushButton * pBtnHome = new Wt::WPushButton("Home");
    pBtnHome->setStyleClass("web-site-menu-style");
    templ->bindWidget( "web-site-home", pBtnHome );
    
    Wt::WPushButton * pBtnNews = new Wt::WPushButton("News");
    pBtnNews->setStyleClass("web-site-menu-style");
    templ->bindWidget( "web-site-news", pBtnNews );
    
    Wt::WPushButton * pBtnTips = new Wt::WPushButton("Travel tips");
    pBtnTips->setStyleClass("web-site-menu-style");
    templ->bindWidget( "web-site-tips", pBtnTips );
    
    Wt::WPushButton * pBtnContacts = new Wt::WPushButton("Contacts");
    pBtnContacts->setStyleClass("web-site-menu-style");
    templ->bindWidget( "web-site-contacts", pBtnContacts );
    
    Wt::WPushButton * pBtnAbout = new Wt::WPushButton("About us");
    pBtnAbout->setStyleClass("web-site-menu-style");
    templ->bindWidget( "web-site-about-us", pBtnAbout );
    
    Wt::WPushButton * pBtnFAQ = new Wt::WPushButton("FAQ's");
    pBtnFAQ->setStyleClass("web-site-menu-style");
    templ->bindWidget( "web-site-faq", pBtnFAQ );
    
    this->addWidget ( templ );
}