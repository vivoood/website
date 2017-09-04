#include <Wt/WApplication>
#include "WebSite.h"

Wt::WApplication *createApplication ( const Wt::WEnvironment& env )
{
    return new WebSite ( env );
}

int main ( int argc, char **argv )
{
    return Wt::WRun ( argc, argv, &createApplication );
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
