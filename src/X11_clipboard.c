#ifdef __linux__
	#include <string.h> //strlen
	#include <time.h> //time_t
	#include <X11/Xlib.h> //X11 functions for copy to clipboard
	#include <stdio.h>
	#include <unistd.h>
	
	#include "../include/X11_clipboard.h"

	/*
	* X11_clipboard: C functions to use the main clipboard object of X11.
	* 90% of this code is borrowed from exebook's barebones implementation: https://github.com/exebook/x11clipboard.
	* I have just added abstraction by merging everything into two simple and easy to use functions in one C program for my own use.
	*
	* Author:
	*	Zander Labuschagne <zander.labuschagne@protonmail.ch>
	*
	* To compile add -X11 argument to gcc to include the X11 libraries.
	* This should only be compatible with Linux systems, if not please inform me.
	* I am still learning C++ so if anything is unacceptable or a violation to some standards please inform me.
	*/

	/*
	 * Function to copy some text to the X11 main clipboard.
	 * text contains text to be copied.
	 * seconds_active states the number of seconds the text will stay on the clipboard.
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
		int i = 0;
		while (time(NULL) < end) { // execute while current time is less than end time
		printf("%d\n", i++);
			XEvent event;
			printf("XEVent\n");
			XNextEvent(display, &event);
			printf("XNextEvent\n");
			switch (event.type) {
				case SelectionRequest:
				{
							printf("case 1\n");

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
				case SelectionClear:
				 	return;
			}
		}
	}

	/*
	 * Function to paste text from the X11 main clipboard.
	 * returns the text on the X11 main clipboard.
	 */
	// char *paste()
	// {
	// 	Display *display = XOpenDisplay(0);
	// 	Atom UTF8 = XInternAtom(display, "UTF8_STRING", 1);
	// 	const Atom XA_STRING = 31;
	// 	Atom atom;
	// 	if (UTF8 != None)
	// 		atom = UTF8;
	// 	if (!atom)
	// 		atom = XA_STRING;
	// 	const Atom XSEL_DATA = XInternAtom(display, "XSEL_DATA", 0);
	// 	const Atom SELECTION = XInternAtom(display, "CLIPBOARD", 0);
	// 	const int N = DefaultScreen(display);
	// 	Window window = XCreateSimpleWindow(display, RootWindow(display, N), 0, 0, 1, 1, 0, BlackPixel(display, N), WhitePixel(display, N));
	// 	XConvertSelection(display, SELECTION, atom, XSEL_DATA, window, CurrentTime);
	// 	XSync(display, 0);
	// 	XEvent event;
	// 	XNextEvent(display, &event);
	// 	char *clipboard = 0;
	// 	switch (event.type) {
	// 	case SelectionNotify:
	// 		if (event.xselection.selection != SELECTION)
	// 			break;
	// 		if (event.xselection.property) {
	// 			char *data;
	// 			int format;
	// 			unsigned long n;
	// 			unsigned long size;
	// 			Atom atom_targets = XInternAtom(display, "TARGETS", 0);
	// 			XGetWindowProperty(event.xselection.display, event.xselection.requestor, event.xselection.property, 0L, (~0L), 0, AnyPropertyType, &atom_targets, &format, &size, &n, (unsigned char**)&data);
	// 			if (atom_targets == UTF8 || atom_targets == XA_STRING) {
	// 				clipboard = strndup(data, size);
	// 				XFree(data);
	// 			}
	// 			XDeleteProperty(event.xselection.display, event.xselection.requestor, event.xselection.property);
	// 		}
	// 		break;
	// 	}

	// 	return clipboard;
	// }
#endif
