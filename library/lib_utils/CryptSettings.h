#include "Singleton.h"
#include "Crypt.h"
#include <crypto++/sha.h>

#ifndef _CRYPTSETTINGS_H
#define _CRYPTSETTINGS_H

class CryptSettings : public Singleton<CryptSettings>
{

    static const std::string KEY_PART_ONE;

    byte m_sha256_buffer[ CryptoPP::SHA256::DIGESTSIZE ];

    byte m_key[ CryptoPP::AES::MAX_KEYLENGTH ], m_iv[ CryptoPP::AES::BLOCKSIZE ];


public:

    CryptSettings();

    ~CryptSettings();

	std::string EncryptSettings( const char* plaintext,
								 unsigned int plaintext_size,
								 const std::string& TAG,
								 const std::string& filename );

	std::string DecryptSettings( const char* ciphertext,
								 unsigned int ciphertext_size,
								 const std::string& TAG,
								 const std::string& filename );

private:

	void CreateKey( const std::string& TAG );

	void CreateIV( const std::string& filename );
};

#endif /*_CRYPTSETTINGS_H*/
