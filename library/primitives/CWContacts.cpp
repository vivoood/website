#include "CWContacts.h"

#include <Wt/WPushButton>
#include <sstream>

class MyWidget : public Wt::WContainerWidget
{
public:
    MyWidget()
        : Wt::WContainerWidget(),
          done_ ( this )
    {
//         ...
        Wt::WPushButton *button = new Wt::WPushButton ( "Okay" );
        this->addWidget ( button );
        button->clicked().connect ( this, &MyWidget::process );
    }
    // provide an accessor for the signal
    Wt::Signal<int, std::string>& done()
    {
        return done_;
    }

private:

    Wt::Signal<int, std::string> done_;

    void process()
    {
//         ...
        done_.emit ( 42, "Totally done" ); // emit the signal
    }
};

CWContacts::CWContacts ( IWidgetData * pD, Wt::WContainerWidget* parent ) : WContainerWidget ( parent )
{
    MyWidget *widget = new MyWidget();
    this->addWidget ( widget );
    widget->done().connect ( this, &CWContacts::f );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 


void CWContacts::f ( int n, std::string str )
{
    std::stringstream ss;
    ss << "id is: " << n << " value is: " << str;

    this->addWidget ( new Wt::WPushButton ( ss.str().c_str() ) );
}
