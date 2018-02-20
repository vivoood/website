#ifndef CWLINEEDITFIELD_H
#define CWLINEEDITFIELD_H

#include <Wt/WContainerWidget>

namespace Wt
{
class WLineEdit;
}

class CWLineEditField : public Wt::WContainerWidget
{
public:
    CWLineEditField ( std::string label, Wt::WContainerWidget* parent = 0 );
    std::string Value();
    Wt::WLineEdit * pEdit = nullptr;
};

#endif // CWLINEEDITFIELD_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
