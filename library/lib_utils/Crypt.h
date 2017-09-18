#ifndef _CRYPT_H
#define _CRYPT_H

#include "crypto++/modes.h"
#include "crypto++/aes.h"
#include "crypto++/filters.h"

#include <iostream>
#include <iomanip>


namespace Crypt
{
    extern byte key[ CryptoPP::AES::MAX_KEYLENGTH ];
    extern byte iv[ CryptoPP::AES::BLOCKSIZE ];

    std::string Encrypt( const char* plaintext, unsigned int plaintext_size, const byte* Key, const byte* IV);

    std::string Decrypt( const char* ciphertext, unsigned int ciphertext_size, const byte* Key, const byte* IV );
}
#endif // _CRYPT_H
