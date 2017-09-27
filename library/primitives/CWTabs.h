#ifndef CWTABS_H
#define CWTABS_H

#include <Wt/WContainerWidget>

#include "IWidgetData.h"

class CWTabs : public Wt::WContainerWidget
{
private:
    friend class Factory;
    CWTabs ( IWidgetData * pD, Wt::WContainerWidget* parent = 0 );
    Wt::WContainerWidget * m_pContent = nullptr;
    void FillFromSignal ( std::string str );
};

#endif // CWTABS_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
