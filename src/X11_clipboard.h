/*
 * X11_clipboard: C functions to use the main clipboard object of X11.
 * 90% of this code is borrowed from exebook's barebones implementation: https://github.com/exebook/x11clipboard
 * I have just added abstraction by merging everything into two simple and easy to use functions in one C++ class for my own use.
 *
 * Author:
 *	Zander Labuschagne <zander.labuschagne@protonmail.ch>
 *
 * To compile add -X11 argument to gcc to include the X11 libraries
 * This should only be compatible with Linux systems, if not please inform me.
 * I am still learning C++ so if anything is unacceptable or a violation to some standards please inform me.
*/

#ifdef __linux__
	#include <string.h>
	#include <time.h>
	#include <X11/Xlib.h>

	void copy(const char *text, long seconds_active);
	char *paste();
#endif
