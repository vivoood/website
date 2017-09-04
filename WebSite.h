/*
 * Velislav Velkov
 */

#ifndef WEBSITE_H
#define WEBSITE_H

namespace Wt
{
class WApplication;
}

class WebSite : public Wt::WApplication
{
public:
    WebSite ( const Wt::WEnvironment& env );
};

#endif // WEBSITE_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
