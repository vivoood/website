#include "Debug.h"

#include <execinfo.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <iomanip>
#include <sstream>

void Debug::full_write ( int fd, const char *buf, size_t len )
{
    while ( len > 0 )
    {
        ssize_t ret = write ( fd, buf, len );

        if ( ( ret == -1 ) && ( errno != EINTR ) )
            break;

        buf += ( size_t ) ret;
        len -= ( size_t ) ret;
    }
}

void Debug::print_backtrace ( std::string str )
{
    std::cout << "BACKTRACE -------------------" << str << "-----------------" << std::endl;

    static const char start[] = "------------------------------------------------------------------\n";
    static const char end[] = "------------------------------------------------------------------\n";

    void *bt[1024];
    int bt_size;
    char **bt_syms;
    int i;

    bt_size = backtrace ( bt, 1024 );
    bt_syms = backtrace_symbols ( bt, bt_size );
    Debug::full_write ( STDERR_FILENO, start, strlen ( start ) );
    for ( i = 1; i < bt_size; i++ )
    {
        size_t len = strlen ( bt_syms[i] );
        Debug::full_write ( STDERR_FILENO, bt_syms[i], len );
        Debug::full_write ( STDERR_FILENO, "\n", 1 );
    }
    Debug::full_write ( STDERR_FILENO, end, strlen ( end ) );
    free ( bt_syms );
}

void Debug::print_msg ( std::string msgFrom, std::string msg )
{
    std::cout << std::endl << std::setfill ( '-' ) << std::setw ( 40 ) << "-" << "----------" << std::endl;
    std::cout << std::setfill ( '-' ) << std::setw ( 40 ) << msgFrom << "----------" << std::endl;
    std::cout << std::setfill ( '-' ) << std::setw ( 40 ) << msg << "----------" << std::endl;
    std::cout << std::setfill ( '-' ) << std::setw ( 40 ) << "-" << "----------" << std::endl << std::endl;
}

void Debug::print_msg ( std::string msgFrom, void* p )
{
    if ( nullptr == p )
    {
        Debug::print_msg ( msgFrom, "nullptr" );
        return;
    }

    std::stringstream ss;
    ss << p;
    Debug::print_msg ( msgFrom, ss.str() );

}

void Debug::print_msg ( std::string msgFrom, int n )
{
    std::stringstream ss;
    ss << n;
    Debug::print_msg ( msgFrom, ss.str() );
}

void Debug::print_msg ( std::string msgFrom )
{
    Debug::print_msg ( msgFrom, "" );
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
