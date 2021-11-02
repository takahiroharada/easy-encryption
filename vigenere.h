#pragma once

#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <ctype.h>

using namespace std;

static const std::string AVAILABLE_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";

inline int index(char c) {
	if( 'a' <= c && c <= 'z' )
	{
		return c - 'a';
	}
	if( 'A' <= c && c <= 'Z' )
	{
		return 26 + ( c - 'A' );
	}
	if( '0' <= c && c <= '9' )
	{
		return 26 * 2 + ( c - '0' );
	}
	if( c == ' ')
	{
		return 26 * 2 + 10;
	}

	/* Original
	for(int ii = 0; ii < AVAILABLE_CHARS.size(); ii++) {
		if(AVAILABLE_CHARS[ii] == c) {
			// std::cout << ii << " " << c << std::endl;
			return ii;
		}
	}
	*/
	return -1;
}


inline std::string extend_key(std::string& msg, std::string& key) {
	//generating new key
	int msgLen = msg.size();
	std::string newKey(msgLen, 'x');
	int keyLen = key.size(), i, j;
    for(i = 0, j = 0; i < msgLen; ++i, ++j){
        if(j == keyLen)
            j = 0;
 
        newKey[i] = key[j];
    }
    newKey[i] = '\0';
	return newKey;
}


inline std::string encrypt_vigenere(std::string& msg, std::string& key) {
	int msgLen = msg.size(), keyLen = key.size(), i, j;
 	std::string encryptedMsg(msgLen, 'x');
    // char newKey[msgLen], encryptedMsg[msgLen], decryptedMsg[msgLen];
 
	std::string newKey = extend_key(msg, key);
 
    //encryption
    for(i = 0; i < msgLen; ++i) {
    	// std::cout << msg[i] << " " << isalnum(msg[i]) << std::endl;
    	if(isalnum(msg[i]) || msg[i] == ' ') {
    		encryptedMsg[i] = AVAILABLE_CHARS[((index(msg[i]) + index(newKey[i])) % AVAILABLE_CHARS.size())];
    	} else {
    		encryptedMsg[i] = msg[i];
    	}
    }
	
    encryptedMsg[i] = '\0';
    return encryptedMsg; 
}

inline std::string decrypt_vigenere(std::string& encryptedMsg, std::string& newKey) {
	// decryption
	int msgLen = encryptedMsg.size();
	std::string decryptedMsg(msgLen, 'x');
	int i;
    for(i = 0; i < msgLen; ++i) {
    	if(isalnum(encryptedMsg[i]) || encryptedMsg[i] == ' ') {
    		decryptedMsg[i] = AVAILABLE_CHARS[(((index(encryptedMsg[i]) - index(newKey[i])) + AVAILABLE_CHARS.size()) % AVAILABLE_CHARS.size())];
    	} else {
    		decryptedMsg[i] = encryptedMsg[i];
    	}
    }
    decryptedMsg[i] = '\0';
	return decryptedMsg;
}

