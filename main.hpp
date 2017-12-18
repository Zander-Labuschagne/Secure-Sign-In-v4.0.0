#include "SecureSignIn.hpp"
#include <sstream>
#if defined (__MACH__) || defined(__linux__)
	#include <termios.h>
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
#endif

void display_password(const char* password);
std::string copy_password(const char* password);
std::string copy_password_linux(const char* password);
std::string copy_password_macos(const char* password);
std::string copy_password_windows(const char* password);
std::string exec(const char* tty);
//tty tools, maybe build a library?
void set_echo(bool enabled);
void set_echo_posix(bool enabled);
void set_echo_windows(bool enabled);
void set_buffer(bool enabled);
void set_buffer_posix(bool enabled);
void set_buffer_windows(bool enabled);

void display_password(const char* password)
{
	for(unsigned short xviii = 0; *(password + xviii) != '\0'; xviii++)
		std::cout << *(password + xviii);
	std::cout << std::endl;
}

std::string copy_password(const char* password)
{
	#ifdef _WIN32 //both windows 32-bit and 64-bit; _WIN64 is only 64-bit
		return copy_password_windows(password);
	#elif __APPLE__ //All Apple devices; TARGET_OS_IPHONE for iOS device; TARGET_OS_MAC for macOS
		return copy_password_macos(password);
	#elif __linux__  //__unix__ // all unices not linux or macOS; defined(_POSIX_VERSION) for POSIX system
		return copy_password_linux(password);
	#endif
}

std::string copy_password_linux(const char* password)
{
	return copy_password_macos(password); //TODO: Review this
}

std::string copy_password_macos(const char* password)
{
	unsigned short xvix;
	for(xvix = 0; *(password + xvix) != '\0'; xvix++);
		
	std::stringstream tty;
	tty << "echo \"" << password << "\" | pbcopy";
	
	return exec(tty.str().c_str());
}

std::string copy_password_windows(const char* password)
{
	return copy_password_macos(password); //TODO: Review this

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

std::string exec(const char* tty)
{
	FILE* pipe = popen(tty, "r");
	if (!pipe) 
		return "ERROR";
	char buffer[128];
	std::string result = "";
	while(!feof(pipe))
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	pclose(pipe);
	return result;
}

void set_echo(bool enabled = true)
{
	#if defined(__MACH__) || defined(__linux__)
		set_echo_posix(enabled);
	#elif _WIN32
		set_echo_windows(enabled);
	#endif
}

#if defined(__MACH__) || defined(__linux__) //Inlcudes Apple(macOS, iOS), UNIX
void set_echo_posix(bool enabled = true)
{
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty);
	
	if(!enabled)
		tty.c_lflag &= ~ECHO;
	else
		tty.c_lflag |= ECHO;

	tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}
#elif _WIN32
void set_echo_windows(bool enabled = true)
{
	HANDLE std_handle = GetStdHandle(STD_INPUT_HANDLE); 
	DWORD mode;
	GetConsoleMode(std_handle, &mode);

	if(!enabled)
		mode &= ~ENABLE_ECHO_INPUT;
	else
		mode |= ENABLE_ECHO_INPUT;

	SetConsoleMode(std_handle, mode);
}
#endif

void set_buffer(bool enabled)
{
	#if defined(__MACH__) || defined(__linux__)
		set_buffer_posix(enabled);
	#elif _WIN32
		set_buffer_windows(enabled);
	#endif
}

#if defined(__MACH__) || defined(__linux__)  //Inlcudes Apple(macOS, iOS), Linux, UNIX
void set_buffer_posix(bool enabled)
{
	struct termios tty;
	tcgetattr(STDIN_FILENO, &tty); //get the current terminal I/O structure
	
	if(!enabled)
		tty.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
	else
		tty.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
			
	tcsetattr(STDIN_FILENO, TCSANOW, &tty); //Apply the new settings
}
#elif _WIN32
void set_buffer_windows(bool enabled)
{
	set_buffer_posix(enabled); //TODO: Review this
}
#endif

