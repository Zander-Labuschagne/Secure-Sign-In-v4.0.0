/**
 * Copyright (C) 2019 Zander Labuschagne. All rights reserved.
 * @version 4.0.0
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

#include <sstream>

#if defined (__MACH__) || defined(__linux__)
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
#endif

#include "../include/TTY.hpp"

/**
 * class containing functions to allow interaction with tty session on UNIX systems
 *
 * This should only be compatible with UNIX-like systems, if not please inform me.
 * @version 4.0.0
 * @since 4.0.0
 */

/**
 * function to execute command in tty session as given in tty paramater
 * @version 4.0.0
 * @since 4.0.0
 */
std::string TTY::execute_command(const char *tty)
{
	FILE* pipe = popen(tty, "r");
	if (!pipe) 
		return "ERROR";

	char buffer[128];
	std::string result = "";
	while (!feof(pipe))
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	pclose(pipe);
	
	return result;
}

/**
 * function to toggle the echo mode in terminal for any platform
 * @version 4.0.0
 * @since 4.0.0
 */
void TTY::set_echo(bool enabled = true)
{
	#if defined(__MACH__) || defined(__linux__)
		set_echo_unix(enabled);
	#elif _WIN32
		set_echo_windows(enabled);
	#endif
}

/**
 * function to toggle the byffer for any platform
 * @version 4.0.0
 * @since 4.0.0
 */
void TTY::set_buffer(bool enabled)
{
	#if defined(__MACH__) || defined(__linux__)
		set_buffer_unix(enabled);
	#elif _WIN32
		set_buffer_windows(enabled);
	#endif
}

/**
 * function to toggle the echo mode in terminal for UNIX systems(macOS and Linux)
 * @version 4.0.0
 * @since 4.0.0
 */
#if defined(__MACH__) || defined(__linux__)
	void TTY::set_echo_unix(bool enabled = true)
	{
		tcgetattr(STDIN_FILENO, &tty);
		
		if(!enabled)
			tty.c_lflag &= ~ECHO;
		else
			tty.c_lflag |= ECHO;

		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	}
	
/**
 * function to toggle the echo mode in terminal for Windows systems
 * @version 4.0.0
 * @since 4.0.0
 * TODO: Test this function
 */
#elif _WIN32
	void TTY::set_echo_windows(bool enabled = true) //TODO: Test
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

/**
 * function to toggle the buffer for UNIX systems(macOS and Linux)
 * Inlcudes Apple(macOS, iOS), Linux, UNIX
 * @version 4.0.0
 * @since 4.0.0
 */
#if defined(__MACH__) || defined(__linux__)
	void TTY::set_buffer_unix(bool enabled)
	{
		tcgetattr(STDIN_FILENO, &tty); //get the current terminal I/O structure
		
		if (!enabled)
			tty.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
		else
			tty.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
				
		tcsetattr(STDIN_FILENO, TCSANOW, &tty); //Apply the new settings
	}

/**
 * function to toggle the terminal buffer for Windows systems
 * @version 4.0.0
 * @since 4.0.0
 * TODO: Test this function
 * This probably won't work.
 */
#elif _WIN32
	void TTY::set_buffer_windows(bool enabled)
	{
		set_buffer_posix(enabled);
	}
#endif
