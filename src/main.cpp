//Document:
//export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

#include "main.hpp"

int main(void) //TODO: Add arguments
{
	TTY tty;

	tty.set_echo(false); //Hide input - Also see getch() for C

	std::cout << "Password: ";
	char password[256];
	std::cin.getline(password, 256);
	std::cout << std::endl << "Key: ";
	char key[256];
	std::cin.getline(key, 256);
	std::cout << std::endl;

	tty.set_echo(true);
	tty.set_buffer(false);

	std::cout << "Enter \'s\' to use the short version of the password." << std::endl;
	std::cout << "Enter \'l\' to use the long version of the password. (Default)" << std::endl;
	std::cout << "Enter \'q\' to exit the application." << std::endl;
	char option;
	std::cin >> option;
	std::cout << std::endl;

	SecureSignIn ssi;
	char *cipher_password;

	switch (option) {
	case 's':
		cipher_password =  ssi.encrypt(&(password[0]), &(key[0]), 12);
		break;
	case 'l':
		cipher_password =  ssi.encrypt(&(password[0]), &(key[0]), 32);
		break;
	case 'q':
		return 0;
	default:
		std::cout << "Terminating application due to user disobedience." << std::endl;
		return 0;
	}

	std::cout << "Enter \'c\' to copy the password and exit the application." << std::endl;
	std::cout << "Enter \'v\' to view/display the password on screen and exit the application." << std::endl;
	std::cout << "Enter \'q\' to exit the application." << std::endl;
	std::cin >> option;
	std::cout << std::endl;

	switch (option) {
	case 'c':
		copy_password(cipher_password);
		return 0;
	case 'v':
		display_password(cipher_password);
		return 0;
	case 'q':
		return 0;
	default:
		std::cout << "Terminating application due to user disobedience." << std::endl;
		return 0;
	}

	return 0;
}

void display_password(const char *password)
{
	for (unsigned short xviii = 0; *(password + xviii) != '\0'; xviii++)
		std::cout << *(password + xviii);
	std::cout << std::endl;
}

void copy_password(const char *password)
{
	#ifdef __linux__  //__unix__ // all unices not linux or macOS; defined(_POSIX_VERSION) for POSIX system
		copy_password_linux(password);
	#elif __MACH__ //All Apple devices; TARGET_OS_IPHONE for iOS device; TARGET_OS_MAC for macOS
		copy_password_macos(password);
	#elif _WIN32 //both windows 32-bit and 64-bit; _WIN64 is only 64-bit
		copy_password_windows(password);
	#endif
}

#ifdef __linux__
	void copy_password_linux(const char *password)
	{
		X11_clipboard clipboard;
		clipboard.copy(password, 8);
	}

#elif __MACH__
	void copy_password_macos(const char *password)
	{
		char *trimmed_password;
		trimmed_password = (char*)malloc(256);
		for (unsigned short xix = 0; *(password + xix) != '\0'; xix++)
			*(trimmed_password + xix) = *(password + xix); 

		std::stringstream tty_command;
		tty_command << "echo \"" << trimmed_password << "\" | pbcopy"; //Ek dink pbcopy is unix shll program om te copy. En ek dink die tty stringstream stuur na die terminal.

		TTY tty;
		tty.execute_command(tty_command.str().c_str()); //ek dink die metode stuur commands na die terminal toe

		time_t end = time(NULL) + 8; //set end time to current time + 8 seconds
		while (time(NULL) <= end); //Wait for as long as current time is less than end time
		free(trimmed_password);
		//std::stringstream tty_clear;
		tty_command << "echo \"" << " " << "\" | pbcopy";
		tty.execute_command(tty_command.str().c_str());
	}

#elif _WIN32
	void copy_password_windows(const char *password)
	{
		copy_password_macos(password); //TODO: Review this

		//#include "stdafx.h"
		//#include "windows.h"
		//#include "string.h"
		//#include <direct.h>

	///////////////////////////////////////////////////////////////////////////	
	//	if ( !OpenClipboard() )
	//		{
	//			AfxMessageBox( _T("Cannot open the Clipboard") );
	//			return;
	//		}
	//		// Remove the current Clipboard contents
	//		if( !EmptyClipboard() )
	//		{
	//			AfxMessageBox( _T("Cannot empty the Clipboard") );
	//			return;
	//		}
	//		// Get the currently selected data
	//		HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, 64);
	//		strcpy_s((char*)hGlob, 64, "Current selection\r\n");
	//		// For the appropriate data formats...
	//		if ( ::SetClipboardData( CF_TEXT, hGlob ) == NULL )
	//		{
	//			CString msg;
	//			msg.Format(_T("Unable to set Clipboard data, error: %d"), GetLastError());
	//			AfxMessageBox( msg );
	//			CloseClipboard();
	//			GlobalFree(hGlob);
	//			return;
	//		}
	//		CloseClipboard();
	/////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	//const char* output = "Test";
	//const size_t len = strlen(output) + 1;
	//HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
	//memcpy(GlobalLock(hMem), output, len);
	//GlobalUnlock(hMem);
	//OpenClipboard(0);
	//EmptyClipboard();
	//SetClipboardData(CF_TEXT, hMem);
	//CloseClipboard();
	/////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////
	//#include <Windows.h>
	//char* LoadClipboard()
	//{
	//	static HANDLE clip;
	//	if(OpenClipboard(NULL))
	//	{
	//		clip = GetClipboardData(CF_TEXT);
	//		CloseClipboard();
	//	}
	//	return (char*) clip;
	//}
	//
	//void SaveClipboard(char* text)
	//{
	//	HGLOBAL global = GlobalAlloc(GMEM_FIXED,strlen(text) + 1); //text size + \0 character
	//	memcpy(global,text,strlen(text));  //text size + \0 character
	//	if(OpenClipboard(NULL))
	//	{
	//		EmptyClipboard();
	//		SetClipboardData(CF_TEXT,global);
	//		CloseClipboard();
	//	}
	//}
	///////////////////////////////////////////////////////////////////////////////////


	}
#endif
