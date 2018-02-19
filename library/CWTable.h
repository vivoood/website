#ifndef CWTABLE_H
#define CWTABLE_H

#include <Wt/WTable>
#include <Wt/WTableCell>

class CWTable : public Wt::WTable
{
public:
    CWTable ( Wt::WContainerWidget *parent = 0 );
};

#endif // CWTABLE_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
