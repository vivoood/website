#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <Wt/WWidget>

class Factory
{
public:
    static Wt::WWidget * Create ( std::string str );
};

#endif // FACTORY_H
