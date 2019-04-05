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

#include <string>

#if defined (__MACH__) || defined(__linux__)
	#include <termios.h>
#endif

/**
 * Class containing functions to allow interaction with tty session on UNIX systems.
 *
 * This should only be compatible with UNIX-like systems, if not please inform me.
 * @version 4.0.0
 * @since 4.0.0
 */

class TTY
{
public:
	std::string execute_command(const char *);
	void set_echo(bool);
	void set_buffer(bool);

private:
	struct termios tty;
	void set_echo_unix(bool);
	void set_echo_windows(bool);
	void set_buffer_unix(bool);
	void set_buffer_windows(bool);
};