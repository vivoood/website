/*
 * Velislav Velkov
 */

#include <Wt/WApplication>

#include <dlfcn.h>
#include <string>

#include "WebSite.h"
#include <first_site/MainWidget.h>

uint64_t WebSite::m_nInstanceCounter = 0;

WebSite::WebSite ( const Wt::WEnvironment& env )
    : Wt::WApplication ( env ),
      m_pWebSite ( nullptr ),
      m_handle ( nullptr ),
      m_create ( nullptr ),
      m_destroy ( nullptr )

{
    m_nInstanceCounter++;
    m_nInstanceId = m_nInstanceCounter;
    
    this->setTitle ( "Ivaylo Some Title" );

    this->messageResourceBundle().use ( this->appRoot() + "WebTemplates" );
    this->useStyleSheet ( "WebStyle.css" );

//     m_handle = dlopen ( "./libhangman.so", RTLD_LAZY );
    m_handle = dlopen ( "./libfirst_site.so", RTLD_LAZY );
    if ( !m_handle )
    {
        std::cout << "OPEN: The error is " << dlerror() << std::endl;
    }

    m_create= ( create_t* ) dlsym ( m_handle,"create" );
    m_destroy= ( destroy_t* ) dlsym ( m_handle,"destroy" );

    if ( ( !m_create ) || ( !m_destroy ) )
    {
        std::cout << "USE: The error is " << dlerror() << std::endl;
    }

    m_pWebSite = m_create();
    root()->addWidget ( m_pWebSite );
}

WebSite::~WebSite()
{
    m_destroy ( m_pWebSite );
    dlclose ( m_handle );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
