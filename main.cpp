//Document:

#include "SecureSignIn.hpp"

int main()
{
	SecureSignIn ssi;

	std::cout << "Password: ";
	std::string password;//verander na char
	std::cin >> password;
	std::cout << std::endl << "Key: ";
	std::string key;
	std::cin >> key;
	std::cout << std::endl;

	std::cout << *(ssi.encrypt(&(password[0]), &(key[0]), 32)) << std::endl;

	return 0;
}