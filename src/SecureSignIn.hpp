//
#include <iostream>

class SecureSignIn
{
public:
	char *encrypt(const char *user_password, const char *key, unsigned short limit);
};