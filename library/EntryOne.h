#ifndef ENTRYONE_H
#define ENTRYONE_H

#include <Wt/WApplication>
#include <Wt/WContainerWidget>

namespace Wt
{
class WTableCell;
}

class EntryOne : public Wt::WContainerWidget
{
    Wt::WTableCell * m_pCell = nullptr;
public:
    friend class Factory;
    EntryOne ( Wt::WApplication * pApp );
    void CreateEntry ( std::string strUserHash );
};

#endif // ENTRYONE_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
