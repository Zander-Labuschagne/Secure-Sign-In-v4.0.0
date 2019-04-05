/**
 * Copyright (C) 2019 Zander Labuschagne. All rights reserved.
 * @version 4.0.0 05/04/19
 * @since 4.0.0
 *
 * Authors:
 *         @author Zander Labuschagne <zander.labuschagne@protonmail.ch>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU GPL 2.0 License, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GPL 2.0 License for more details.
 *
 * You should have received a copy of the GNU GPL 2.0 License
 * along with this program; if not, write to the author,
 * contact details above in line 7.
 */

//Document:
//export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

#include <iostream>
#include <sstream>
#include <string.h>

#include "../include/main.hpp"
#include "../include/SecureSignIn.hpp"
#include "../include/TTY.hpp"

#ifdef __linux__
	#include "../include/X11_clipboard.h"
#endif

/**
 * Main Secure Sign In program (entry point).
 * @version 4.1.0
 * @since 4.0.0
*/
int main(int argc, char **argv)
{
	char option1 = '.';
	char option2 = '.';

	for (unsigned short arg = 1; arg < argc; arg++) {
		if (strlen(argv[arg]) < 2) {
			std::cerr << "Argument \"" << argv[arg] << "\" is not defined in Secure Sign In v4.1.x" << std::endl << "Try 'ssi --help' for more information." << std::endl;
			return 0;
		}
		if (strlen(argv[arg]) > 2 && argv[arg][0] == '-' && argv[arg][1] == '-') {
			if (strcmp(argv[arg], "--long") == 0)
				option1 = 'l';
			else if (strcmp(argv[arg], "--short") == 0)
				option1 = 's';
			else if (strcmp(argv[arg], "--copy") == 0)
				option2 = 'c';
			else if (strcmp(argv[arg], "--verbose") == 0)
				option2 = 'v';
			else if (strcmp(argv[arg], "--help") == 0) {
				print_help();
				return 0;
			}
			else {
				std::cerr << "Argument \"" << argv[arg] << "\" is not defined in Secure Sign In v4.1.x" << std::endl << "Try 'ssi --help' for more information." << std::endl;
				return 0;
			}
		}
		else if (strlen(argv[arg]) >= 2 && argv[arg][0] == '-') {
			for (unsigned short xx = 1; xx < strlen(argv[arg]); ++xx) {
				switch (argv[arg][xx]) {
				case 'l':
					option1 = 'l';
					break;
				case 's':
					option1 = 's';
					break;
				case 'c':
					option2 = 'c';
					break;
				case 'v':
					option2 = 'v';
					break;
				case 'h':
					print_help();
					return 0;
				default:
					std::cerr << "Argument \"" << argv[arg] << "\" is not defined in Secure Sign In v4.1.x" << std::endl << "Try 'ssi --help' for more information." << std::endl;
					return 0;
				}
			}
		} else {
				std::cerr << "Argument \"" << argv[arg] << "\" is not defined in Secure Sign In v4.1.x" << std::endl << "Try 'ssi --help' for more information." << std::endl;
				return 0;
		}
	}

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

	if (option1 == '.') {
		std::cout << "Enter \'s\' to use the short version of the password." << std::endl;
		std::cout << "Enter \'l\' to use the long version of the password. (Default)" << std::endl;
		std::cout << "Enter \'q\' to exit the application." << std::endl;
		std::cin >> option1;
		std::cout << std::endl;
	}

	SecureSignIn ssi;
	char *cipher_password;

	switch (option1) {
	case 's':
		cipher_password =  ssi.encrypt(&(password[0]), &(key[0]), 12);
		break;
	case 'l':
		cipher_password =  ssi.encrypt(&(password[0]), &(key[0]), 32);
		break;
	case 'q':
		return 0;
	default:
		std::cerr << "Terminating application due to user disobedience." << std::endl << "Try 'ssi --help' for more information." << std::endl;
		return 0;
	}

	if (option2 == '.') {
		std::cout << "Enter \'c\' to copy the password and exit the application." << std::endl;
		std::cout << "Enter \'v\' to view/display the password on screen and exit the application." << std::endl;
		std::cout << "Enter \'q\' to exit the application." << std::endl;
		std::cin >> option2;
		std::cout << std::endl;
	}

	switch (option2) {
	case 'c':
		copy_password(cipher_password);
		free(cipher_password);
		return 0;
	case 'v':
		display_password(cipher_password);
		free(cipher_password);
		return 0;
	case 'q':
		free(cipher_password);
		return 0;
	default:
		std::cerr << "Terminating application due to user disobedience." << std::endl << "Try 'ssi --help' for more information." << std::endl;
		free(cipher_password);
		return 0;
	}

	return -1;
}

void print_help() //TODO: Maak 'n man page
{
	std::cout << "Secure Sign In v4.1a ( https://gitlab.com/Zander-Labuschagne/SecureSignIn-v4a )" << std::endl;
	
	std::cout << std::endl;
	std::cout << "Usage: ssi [OPTIONS]..." << std::endl;
	std::cout << "\t-l, --long\t\tLong(Default) version of the password" << std::endl;
	std::cout << "\t-s, --short\t\tShort version of the password" << std::endl;
	std::cout << "\t-c, --copy\t\tCopies the password to memory for 8 seconds before it is removed from memory" << std::endl; //TODO: Maybe add an argument option to specify the number of seconds the password stays in RAM
	std::cout << "\t-v, --verbose\t\tDisplays the password on the terminal screen if needed to type over manually" << std::endl << "\t\t\t\t(not safe -- only use when absolutely necessary)" << std::endl;
	std::cout << "\t-h, --help\t\tDisplays this help menu" << std::endl;
	
	std::cout << std::endl;
	std::cout << "EXAMPLES:" << std::endl;
	std::cout << "\tssi -lc" << std::endl;
	std::cout << "\tssi -l -c" << std::endl;
	std::cout << "\tssi -c" << std::endl;
	std::cout << "\tssi --long --copy" << std::endl;
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
		//X11_clipboard clipboard;
		//clipboard.copy(password, 8);
		copy(password, 8);
	}

#elif __MACH__
	void copy_password_macos(const char *password)
	{
		char *trimmed_password;
		trimmed_password = (char*)malloc(256);
		for (unsigned short xix = 0; *(password + xix) != '\0'; xix++)
			*(trimmed_password + xix) = *(password + xix); 

		std::stringstream tty_command;
		tty_command << "echo \"" << trimmed_password << "\" | pbcopy"; //Ek dink pbcopy is unix shell program om te copy. En ek dink die tty stringstream stuur na die terminal.

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
