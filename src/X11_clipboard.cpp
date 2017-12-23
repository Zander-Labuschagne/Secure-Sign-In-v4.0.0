#ifdef __linux__
	#include "X11_clipboard.hpp"

	void X11_clipboard::copy(const char *text, long seconds_active)
	{
		int size = strlen(text);
		if (UTF8 == None)
			UTF8 = XA_STRING;

		XSetSelectionOwner(display, SELECTION, window, 0);
		if (XGetSelectionOwner(display, SELECTION) != window)
			return;

		time_t end = time(NULL) + seconds_active; //declare end time equal to current time + seconds_active seconds
		while (time(NULL) <= end) { // execute while current time is less than end time
			XNextEvent(display, &event);
			switch (event.type) {
			case SelectionRequest:
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
	
	char *X11_clipboard::paste()
	{
		Atom atom;
		if (UTF8 != None)
			atom = UTF8;
		if (!atom)
			atom = XA_STRING;
		const Atom XSEL_DATA = XInternAtom(display, "XSEL_DATA", 0);
		XConvertSelection(display, SELECTION, atom, XSEL_DATA, window, CurrentTime);
		XSync(display, 0);
		XNextEvent(display, &event);
		char *clipboard = 0;
		switch (event.type) {
		case SelectionNotify:
			if (event.xselection.selection != SELECTION)
				break;
			if (event.xselection.property) {
				char *data;
				int format;
				unsigned long n;
				unsigned long size;
				XGetWindowProperty(event.xselection.display, event.xselection.requestor, event.xselection.property, 0L, (~0L), 0, AnyPropertyType, &atom_targets, &format, &size, &n, (unsigned char**)&data);
				if (atom_targets == UTF8 || atom_targets == XA_STRING) {
					clipboard = strndup(data, size);
					XFree(data);
				}
				XDeleteProperty(event.xselection.display, event.xselection.requestor, event.xselection.property);
			}
			break;
		}
		
		return clipboard;
	}
#endif
