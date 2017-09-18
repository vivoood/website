#!/bin/bash
echo '#include <iostream>
#include <fstream>
#include <sstream>

#include "CryptSettings.h"

int main(int argc, char *argv[])
{
    if(argc != 3) {
        std::cout << "Usage: " << argv[0] << " <file to decrypt> <file to store decrypted image>" << std::endl;
        return 0;
    }

    std::string sInputFileName(argv[1]);
    std::string sOutputFileName(argv[1]);
    
    std::ifstream ifsFile( argv[1], std::ifstream::in | std::ifstream::binary );
    std::ofstream ofsFile( argv[2], std::ifstream::out );

    if ( !ifsFile.is_open() )
    {
        std::cout << "Failed to open input file!" << std::endl;
        return 1;
    }

    if ( !ofsFile.is_open() )
    {
        std::cout << "Failed to open output file!" << std::endl;
        return 1;
    }
        
    std::ostringstream ssEncryptedData;
    ssEncryptedData << ifsFile.rdbuf();

    std::string sOnlyFileName = sInputFileName.substr( sInputFileName.find_last_of("/\\") + 1 );
    std::string sTagVersion = sOnlyFileName.substr(0, sOnlyFileName.find_last_of("~") );
    std::string sDecryptedData = CryptSettings::Instance().DecryptSettings( ssEncryptedData.str().c_str(),
                                                                            ssEncryptedData.str().size(),
                                                                            sTagVersion,
                                                                            sOnlyFileName );
    ofsFile << sDecryptedData << std::endl;

    return 0;
}' > main.cpp
g++ -g Crypt.cpp CryptSettings.cpp main.cpp -lcrypto++ -o decrypt-exported-settings
rm main.cpp
