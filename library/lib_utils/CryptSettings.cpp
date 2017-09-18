#include "CryptSettings.h"
#include "Crypt.h"

const std::string CryptSettings::KEY_PART_ONE("LNDOdytMKJGdskcSvHl06D7sAyuQCQ5sLm5zzBcTF2uPAYms8FQlNGo6c4BerpK22N7u5k19cOjSY9UFoRas+XRXjNUpdUmCbx2ptpsZsaJsB1wIs0g3OCnKzNqxjcKYaV6bBmjR0LRcnQhfVmaeB39sGVwl5SVtIY/sSjk7vu1e8+NHA0VHp6C987UmZ0qj3PfTWv5SvcN/sWjRmp77HYskWU7QsQAYJ6maZlSROozktJ9oWw1/G6cjkbDVugDhoX25RQYSJvQ0U1pe15sQnheOunpoupuimOjqew9bZguiZc3moanKGwRFx8oG/afoL1LmAucGqWygZJebP23ufqMudTK/vY2xdhpHH3y42UkuqMqpTtWjEwrPjUZVC8XBuTz508k5Dy/caCayYphiM2ZyquRi7shBhJInngZ9JgkZnhfekwLSQ7RIQhhR6RN9A0CyHkZmAgccTtZfqtl7wQgTDTbxPCFu7smKaouyaNQIYNegVDeoN2EOVMvWW7OeAa3yBcWrGHsNQVB3udPtgmH77UtrevS+ZlfFDPpRcXeEhxw8ygdq62elzg37CgH7gO4jjusBErSX3KOx2AOWIVU0e53aRsk3SZq4rE49wiIYqwTaMev0LeRG7udsfzI0/oeuSn4m0mc4WieECXGrIpOsZlDsdF3b5p4ssY/1QPLfvKSOHcpFv1uUflCoKW/MFzXwcgs/ZOP4xbQ8nYwwT2h5sEIHMp8bhUvT09LODlHtR23fT+r0cGWcXH+MM0fOd4Vf1qIBIdcU4H4pNbJmquc1xgpHkhTVx5P+K8mQ3MNqNNNj0qrGlNpvWl4Y4PYVDSLe+Isjarpp8NqIMPeEZC8hjdrh8PksdX7m0fL7jqu3Dg2RuI/9gzhPxpKEdvl2YAG7WswM4zdtrAzWAbXf9ZiSO213vZFHm7RkVzkYQjkURinxphBR1v0yVeWPCl/5nCyzb29ZWJxQOGQkuaB/eYerfa3+9JAVFeCEHgbFteO0SzKtaoOqwLKWi3M83CtruS6Rrl/k2FXXiEZ1KRjFj3uZQ2Akleddxu4bOSA3zJ8AutIwnz3WFJvKXYUzJJmL2iP+zMhRK4/YhTwV6+QmF6uNoIdSZ3NSMERa+9VNcQ/CTAS3ZQxCN8x17ImkpTw/IY6oa9/0wdYgIG8tb0xtl19f14CVKgl3f/bb5wR/rwxfXnNa0mUAz889fVVWI8rKpuPPpiPtdwSioEPI2prex3AsDvwA9qPNz30eVs0Tuf/LCjb9tAn8AUCV+RxkXjrNqn+PHd+TuufVGEY5II1qkj0gEFP9pSjYTJg+gcxw4BabWBDo8Qu5/sPG+bUYoAvLZSzaCqgKLlrqy4INqX7yQQ");

CryptSettings::CryptSettings()
{
    memset(m_sha256_buffer, 0, CryptoPP::SHA256::DIGESTSIZE);
    memset(m_key, 0, CryptoPP::AES::MAX_KEYLENGTH);
    memset(m_iv, 0, CryptoPP::AES::BLOCKSIZE);
}

CryptSettings::~CryptSettings()
{
}

std::string CryptSettings::EncryptSettings( const char* plaintext,
											unsigned int plaintext_size,
											const std::string& TAG,
											const std::string& filename)
{
    CreateKey(TAG);
    CreateIV(filename);

    return Crypt::Encrypt(plaintext, plaintext_size, m_key, m_iv);
}

std::string CryptSettings::DecryptSettings( const char* ciphertext,
											unsigned int ciphertext_size,
											const std::string& TAG,
											const std::string& filename)
{
    CreateKey(TAG);
    CreateIV(filename);

    return Crypt::Decrypt(ciphertext, ciphertext_size, m_key, m_iv);

}

void CryptSettings::CreateKey( const std::string& TAG )
{
    CryptoPP::SHA256 sha;
    sha.Update((unsigned char*)KEY_PART_ONE.c_str(), KEY_PART_ONE.size());
    sha.Update((unsigned char*)TAG.c_str(), TAG.size());
    sha.Final((unsigned char*)m_sha256_buffer);
    memcpy(m_key, m_sha256_buffer, CryptoPP::AES::MAX_KEYLENGTH);
}

void CryptSettings::CreateIV( const std::string& filename )
{
    CryptoPP::SHA256 sha;
    sha.Update((unsigned char*)filename.c_str(), filename.size());
    sha.Final((unsigned char*)m_sha256_buffer);
    memcpy(m_iv, m_sha256_buffer, CryptoPP::AES::BLOCKSIZE);
}
