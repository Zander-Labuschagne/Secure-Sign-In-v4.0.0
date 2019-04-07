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

/**
* X11_clipboard: C functions to use the main clipboard object of X11.
* 90% of this code is borrowed from exebook's barebones implementation: https://github.com/exebook/x11clipboard.
* I have just added abstraction by merging everything into two simple and easy to use functions in one C program for my own use.
*
* To compile add -X11 argument to gcc to include the X11 libraries.
* This should only be compatible with Linux systems, if not please inform me.
* I am still learning C++ so if anything is unacceptable or a violation to some standards please inform me.
* @version 4.0.0
* @since 4.0.0
*/

#ifdef __linux__
	void copy(const char *, const long);
#endif
