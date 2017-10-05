#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <Wt/WContainerWidget>

class MainWidget : public Wt::WContainerWidget
{
public:
    MainWidget ( WContainerWidget * perant = nullptr );
private:
    void UserLogin ( std::string strHash );
};

#endif // MAINWIDGET_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
