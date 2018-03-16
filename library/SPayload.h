#ifndef SPAYLOAD_H
#define SPAYLOAD_H

#include <string>

class SPayload
{
private:
    SPayload() {}
    std::string data;
    bool IsHeaderOnly(int & found_pos);
public:
    SPayload ( std::string d );
    void Dispatch( std::string & header, std::string & body );
};

#endif // SPAYLOAD_H
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
