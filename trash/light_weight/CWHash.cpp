#include "CWHash.h"

#include <sstream>
#include <iomanip>
#include <crypto++/sha.h>

std::string CWHash::Get ( std::string s )
{
    std::string hstr = "5345@asd#" + s + "fslkdjf34";
    CryptoPP::SHA1 hash;
    unsigned char _sha1[ CryptoPP::SHA1::DIGESTSIZE ];
    hash.CalculateDigest ( _sha1, ( byte* ) s.c_str(), s.length() );

    const unsigned char * Bytes = _sha1;
    size_t Length = CryptoPP::SHA1::DIGESTSIZE;

    std::ostringstream os;
    os.fill ( '0' );
    os << std::hex;
    for ( const unsigned char * ptr=Bytes; ptr<Bytes+Length; ptr++ )
        os << std::setw ( 2 ) << ( unsigned int ) *ptr;

    return os.str();
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
