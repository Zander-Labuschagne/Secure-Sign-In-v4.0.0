//Document:

#include "main.hpp"

int main()
{
	//Hide input - Also see getch() for C
//	termios oldt;
//	tcgetattr(STDIN_FILENO, &oldt);
//	termios newt = oldt;
//	newt.c_lflag &= ~ECHO;
//	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	
	set_echo(false);
	
	std::cout << "Password: ";
	char password[256];
	std::cin.getline(password, 256);
	std::cout << std::endl << "Key: ";
	char key[256];
	std::cin.getline(key, 256);
	std::cout << std::endl;
	
	set_echo(true);
	set_buffer(false);
	
	std::cout << "Enter \'s\' to use the short version of the password." << std::endl;
	std::cout << "Enter \'l\' to use the long version of the password. (Default)" << std::endl;
	std::cout << "Enter \'q\' to exit the application." << std::endl;
	char option;
	std::cin >> option;
	
	SecureSignIn ssi;
	char* cipher_password;
	
	switch(option)
	{
		case('s'):
			cipher_password =  ssi.encrypt(&(password[0]), &(key[0]), 12);
			break;
		case('l'):
			cipher_password =  ssi.encrypt(&(password[0]), &(key[0]), 32);
			break;
		case('q'):
			return 0;
		default:
			std::cout << "Terminating application due to user disobedience." << std::endl;
			return 0;
	}
	
	std::cout << "Enter \'c\' to copy the password and exit the application." << std::endl;
	std::cout << "Enter \'v\' to view/display the password on screen and exit the application." << std::endl;
	std::cout << "Enter \'q\' to exit the application." << std::endl;
	std::cin >> option;
	
	switch(option)
	{
		case('c'):
			copy_password(cipher_password);
			return 0;
		case('v'):
			display_password(cipher_password);
			return 0;
		case('q'):
			return 0;
		default:
			std::cout << "Terminating application due to user disobedience." << std::endl;
			return 0;
	}
	
	return 0;
}
