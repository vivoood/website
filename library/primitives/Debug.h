#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

class Debug
{
    static void full_write ( int fd, const char *buf, size_t len );
public:
    static void print_backtrace ( void );
};

#endif // DEBUG_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
