/*
 * Velislav Velkov
 */

#include <Wt/WApplication>

#include <string>

#include "WebSite.h"
#include "HangmanWidget.h"

WebSite::WebSite ( const Wt::WEnvironment& env ) : Wt::WApplication ( env )
{
    this->setTitle ( "Ivaylo Some Title" );

    this->messageResourceBundle().use ( this->appRoot() + "WebTemplates" );
    this->useStyleSheet ( "WebStyle.css" );

    root()->addWidget ( new HangmanWidget ( std::string ( "Velko" ) ) );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
