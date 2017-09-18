#include "Crypt.h"

byte Crypt::key[ CryptoPP::AES::MAX_KEYLENGTH ];
byte Crypt::iv[ CryptoPP::AES::BLOCKSIZE ];


std::string Crypt::Encrypt( const char* plaintext, unsigned int plaintext_size, const byte* Key, const byte* IV)
{
    if(plaintext == NULL)
    {
      return "";
    }

    std::string dataStr(plaintext);

    if (dataStr.empty())
    {
        return "";
    }

    if(Key == NULL) {
        memset( key, 0x00, CryptoPP::AES::MAX_KEYLENGTH );
    } else {
        memcpy( key, Key, CryptoPP::AES::MAX_KEYLENGTH );
    }

    if(IV == NULL) {
        memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
    } else {
        memcpy( iv, IV, CryptoPP::AES::BLOCKSIZE );
    }

    //
    std::string ciphertext;

    // Create Cipher Text
    //
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::MAX_KEYLENGTH);

    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext ), plaintext_size );
    stfEncryptor.MessageEnd();

    return ciphertext;

}

std::string Crypt::Decrypt( const char* ciphertext, unsigned int ciphertext_size, const byte* Key, const byte* IV )
{
    if(ciphertext == NULL)
    {
      return "";
    }

    std::string dataStr(ciphertext);

    if (dataStr.empty())
    {
        return "";
    }

    if(Key == NULL) {
        memset( key, 0x00, CryptoPP::AES::MAX_KEYLENGTH );
    } else {
        memcpy( key, Key, CryptoPP::AES::MAX_KEYLENGTH );
    }

    if(IV == NULL) {
        memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
    } else {
        memcpy( iv, IV, CryptoPP::AES::BLOCKSIZE );
    }

    std::string decryptedtext;

    //
    // Decrypt
    //
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::MAX_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext ), ciphertext_size );
    stfDecryptor.MessageEnd();

    return decryptedtext;

}