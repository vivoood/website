#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>

class Debug
{
    static void full_write ( int fd, const char *buf, size_t len );
public:
    static void print_backtrace ( std::string str );
    static void print_msg ( std::string msgFrom, std::string msg );
    static void print_msg ( std::string msgFrom, void * p );
    static void print_msg ( std::string msgFrom, int n );
    static void print_msg ( std::string msgFrom );
};

#endif // DEBUG_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
