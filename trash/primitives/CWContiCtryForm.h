#ifndef CWCONTICTRYFORM_H
#define CWCONTICTRYFORM_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

namespace Wt
{
    class WComboBox;
    class WLineEdit;
}

class CWContiCtryForm : public Wt::WContainerWidget
{
public:
    Wt::WComboBox * continents = nullptr;
    Wt::WComboBox * country = nullptr;
    Wt::WLineEdit * city = nullptr;
    void SetLabel ( std::string str );
private:
    friend class Factory;
    CWContiCtryForm ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
    WidgetData::SContiCtry * p = nullptr;
    Wt::WTable * table = nullptr;
    Wt::WContainerWidget * pContainer = nullptr;
    std::vector< std::string > GetConti ();
    std::vector< std::string > GetCtry ( std::string str );
    void Create ( IWidgetData * pD, Wt::WContainerWidget * container, std::string continent );
    void Format ( Wt::WWidget * item );
    std::string strLabel = "n/a";
};

#endif //CWCONTICTRYFORM_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


