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

#ifdef __linux__
	#include <string.h>
	#include <time.h>
	#include <X11/Xlib.h>
	
	#include "../include/X11_clipboard.h"

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

	/**
	 * Function to copy some text to the X11 main clipboard.
	 * text contains text to be copied.
	 * seconds_active states the number of seconds the text will stay on the clipboard.
	 * @version 4.0.0
	 * @since 4.0.0
	 */
	void copy(const char *text, long seconds_active)
	{
		Display *display = XOpenDisplay(0);
		Atom UTF8 = XInternAtom(display, "UTF8_STRING", 1);
		const Atom XA_STRING = 31;
		int size = strlen(text);
		if (UTF8 == None)
			UTF8 = XA_STRING;

		const Atom SELECTION = XInternAtom(display, "CLIPBOARD", 0);
		const int N = DefaultScreen(display);
		Window window = XCreateSimpleWindow(display, RootWindow(display, N), 0, 0, 1, 1, 0, BlackPixel(display, N), WhitePixel(display, N));
		XSetSelectionOwner(display, SELECTION, window, 0);
		if (XGetSelectionOwner(display, SELECTION) != window)
			return;

		time_t end = time(NULL) + seconds_active; //declare end time equal to current time + seconds_active seconds
		while (time(NULL) <= end) { // execute while current time is less than end time
			XEvent event;
			XNextEvent(display, &event);
			// switch (event.type) {
			// case SelectionRequest:
			if (event.type == SelectionRequest) {
			// printf("%d \t %d\n", time(NULL), end);
				if (event.xselectionrequest.selection != SELECTION)
					break;
				XSelectionRequestEvent* xsre = &event.xselectionrequest;
				XSelectionEvent xse = {0};
				int r = 0;
				const Atom XA_ATOM = 4;
				const Atom ATOM_TEXT = XInternAtom(display, "TEXT", 0);
				xse.type = SelectionNotify;
				xse.display = xsre->display;
				xse.requestor = xsre->requestor;
				xse.selection = xsre->selection;
				xse.time = xsre->time;
				xse.target = xsre->target;
				xse.property = xsre->property;
				Atom atom_targets = XInternAtom(display, "TARGETS", 0);
				if (xse.target == atom_targets)
					r = XChangeProperty(xse.display, xse.requestor, xse.property, XA_ATOM, 32, PropModeReplace, (unsigned char*)&UTF8, 1);
				else if (xse.target == XA_STRING || xse.target == ATOM_TEXT)
					r = XChangeProperty(xse.display, xse.requestor, xse.property, XA_STRING, 8, PropModeReplace, (unsigned char*)text, size);
				else if (xse.target == UTF8)
					r = XChangeProperty(xse.display, xse.requestor, xse.property, UTF8, 8, PropModeReplace, (unsigned char*)text, size);
				else
					xse.property = None;
				if ((r & 2) == 0)
					XSendEvent(display, xse.requestor, 0, 0, (XEvent*)&xse);
				break;
			}
		}
	}
#endif
