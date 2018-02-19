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

    m_pWebSite = new EntryOne ( this );
    root()->addWidget ( m_pWebSite );
}

WebSite::~WebSite()
{
    --m_nInstanceCounter;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
