/*
 * Velislav Velkov
 */

#ifndef WEBSITE_H
#define WEBSITE_H

namespace Wt
{
class WApplication;
class WWidget;
}

class WebSite : public Wt::WApplication
{
public:
    WebSite ( const Wt::WEnvironment& env );
    virtual ~WebSite();
private:
    Wt::WWidget* m_pWebSite;
    static uint64_t m_nInstanceCounter;
    uint64_t m_nInstanceId;
};

#endif // WEBSITE_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
