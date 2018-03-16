#include "SPayload.h"

SPayload::SPayload ( std::string d )
{
    data = d;
}

bool SPayload::IsHeaderOnly ( int & found_pos )
{
    found_pos = data.find ( ':' );
    return bool ( found_pos == std::string::npos );
}

void SPayload::Dispatch ( std::string & header, std::string & body )
{
    int found_pos = -1;
    if ( IsHeaderOnly ( found_pos ) )
    {
        header = data;
        body = "";
    }
    else
    {
        header = data.substr ( 0, found_pos );
        body = data.substr ( found_pos + 1 );
    }
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
