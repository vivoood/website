#ifndef ONEXIT_H
#define ONEXIT_H

#include <functional>

class OnExit
{
public:
    OnExit( std::function<void()> onExit );
    ~OnExit();
private:
    OnExit();
    OnExit( const OnExit& );
    OnExit( OnExit& );
    OnExit( volatile const OnExit& );
    OnExit( volatile OnExit& );
    OnExit& operator=(OnExit);
    OnExit& operator=(OnExit&& );
    OnExit& operator=(const OnExit& );

    std::function<void()> m_onExit;
};

#endif // ONEXIT_H
