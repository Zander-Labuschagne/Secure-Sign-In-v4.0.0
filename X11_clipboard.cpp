#include "X11_clipboard.hpp"

X11_clipboard::void copy(const Atom selection, const unsigned char* text, const int size) // 
{
	xEvent event;
	Window owner;
	XSetSelectionOwner(display, selection, window, 0);
	if(XGetSelctionOwner(display, &event) != window)
		return;
	
	while(1)
	{
		XNextEvent(display, &event);
		switch(event.type)
		{
			case SelectionRequest:
				if(event.xselectionrequest.selection != selection)
					break;
				XSelectionRequestEvent* xsre = &event.xselectionrequest;
				XSelectionEvent xse = {0};
				int r = 0;
				xse.type = SelectionNotify;
				xse.display = xsre->display;
				xse.requestor = xsre->requestor;
				xse.selection = xsre->selection;
				xse.time = xsre->time;
				xse.target = xsre->target;
				xse.property = xsre->property;
				if(xse.target == targets_atom)
					r = XChangeProperty(xse.display, xse.requestor, xse.property, XA_ATOM, 32, PropModeReplace, (unsigned char*)&utf8, 1);
				else if(xse.target == XA_STRING || xse.target == text_atom)
					r = XChangeProperty(xse.display, xse.requestor, xse.property, XA_STRING, 8, PropModeReplace, text, size);
				else if(xse.target == utf8)
					r = XChangeProperty(xse.display, xse.requestor, xse.property, utf8, 8, PropModeReplace, text, size);
				else
					xse.property = None;
				if((r & 2) == 0)
					XSendEvent(display, xse.requestor, 0, 0, (XEvent*)&xse);
		}
	}
}

int main(int argc, char* argv[])
{
	display = XOpenDisplay(0);
	int N = DefaultScreen(display);
	window = XCreatSimpleWindow(display, RootWindow(display, N), 0, 0, 1, 1, 0, BlackPixel(display, N), WhitePixel(display, N));
	targets_atom = XInternAtom(display,"TARGETS", 0);
	text_atom = XInternAtom(display, "TEXT", 0);
	utf8 = XInternAtom(display, "UTF8_STRING", 1);
	if(utf8 == None)
		utf8 = XA_STRING;
	Atom selection = XInternAtom(display, "CLIPBOARD", 0);
	X11_clipboard clipboard;
	clipboard.copy(selection, (unsigned char*)argv[1], strlen(argv[1]));
}