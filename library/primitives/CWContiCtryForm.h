#ifndef CWCONTICTRYFORM_H
#define CWCONTICTRYFORM_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWContiCtryForm : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWContiCtryForm ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
    WidgetData::SContiCtry * p = nullptr;
    Wt::WContainerWidget * pContainer = nullptr;
    std::vector< std::string > GetConti ();
    std::vector< std::string > GetCtry ( std::string str );
    void Create ( IWidgetData * pD, Wt::WContainerWidget * container, std::string continent );
    void Format ( Wt::WWidget * item );
};

#endif //CWCONTICTRYFORM_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


