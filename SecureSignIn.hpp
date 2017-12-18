//
#include <iostream>

class SecureSignIn
{
private:
	//char* plain_password;
	//char* key;
	//char* cipher_password;

public:
	SecureSignIn();
	char* encrypt(const char* user_password, const char* key, const unsigned short limit);
	~SecureSignIn();
};