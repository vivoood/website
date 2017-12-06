/*
 * Velislav Velkov
 */

#ifndef WTABLELAYOUT_H
#define WTABLELAYOUT_H

#include <Wt/WContainerWidget>

#include <vector>
#include <string>

class CWTableLayout  : public Wt::WContainerWidget
{
public:
    using TABLE = std::vector< std::vector< std::string > >;
    CWTableLayout ( TABLE tdat, std::string strHash, Wt::WContainerWidget* parent = 0 );
};

#endif // WTABLELAYOUT_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
