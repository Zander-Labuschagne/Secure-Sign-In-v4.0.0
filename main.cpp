//Document:g

#include "SecureSignIn.hpp"

int main()
{
	SecureSignIn ssi;

	std::cout << "Password: ";
	char password[256];
	std::cin.getline(password, 256);
	std::cout << "Key: ";
	char key[256];
	std::cin.getline(key, 256);

	char* cipher_password = ssi.encrypt(&(password[0]), &(key[0]), 32);

	unsigned short i = 0;
	while(*(cipher_password + i) != '\0')
		std::cout << *(cipher_password + i++);
	std::cout << std::endl;

	return 0;
}