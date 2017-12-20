#include "X11_clipboard.hpp"

void X11_clipboard::copy(const Atom selection, const unsigned char* text, const int size) // 
{
	XEvent event;
	Window owner;
	XSetSelectionOwner(display, selection, window, 0);
	if(XGetSelectionOwner(display, selection) != window)
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
	X11_clipboard clipboard;
	clipboard.display = XOpenDisplay(0);
	int N = DefaultScreen(clipboard.display);
	clipboard.window = XCreateSimpleWindow(clipboard.display, RootWindow(clipboard.display, N), 0, 0, 1, 1, 0, BlackPixel(clipboard.display, N), WhitePixel(clipboard.display, N));
	clipboard.targets_atom = XInternAtom(clipboard.display,"TARGETS", 0);
	clipboard.text_atom = XInternAtom(clipboard.display, "TEXT", 0);
	clipboard.utf8 = XInternAtom(clipboard.display, "UTF8_STRING", 1);
	if(clipboard.utf8 == None)
		clipboard.utf8 = clipboard.XA_STRING;
	Atom selection = XInternAtom(clipboard.display, "CLIPBOARD", 0);
	clipboard.copy(selection, (unsigned char*)argv[1], strlen(argv[1]));
}