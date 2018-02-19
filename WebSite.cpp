/*
 * Velislav Velkov
 */

#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <string>

#include "WebSite.h"
#include "library/EntryOne.h"

uint64_t WebSite::m_nInstanceCounter = 0;

WebSite::WebSite ( const Wt::WEnvironment& env )
    : Wt::WApplication ( env ),
      m_pWebSite ( nullptr )
{
    ++m_nInstanceCounter;
    m_nInstanceId = m_nInstanceCounter;

    this->setTitle ( "Change Title" );

    this->messageResourceBundle().use ( this->appRoot() + "WebTemplates" );
    this->useStyleSheet ( "WebStyleLW.css" );

    m_pWebSite = new EntryOne ( nullptr );
    root()->addWidget ( m_pWebSite );
}

WebSite::~WebSite()
{
    --m_nInstanceCounter;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
