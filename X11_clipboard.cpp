#include "X11_clipboard.hpp"

void X11_clipboard::copy(const unsigned char* TEXT, const int SIZE) // 
{
	if(utf8 == None)
			utf8 = XA_STRING;
	
	XEvent event;
	Window owner;
	XSetSelectionOwner(DISPLAY, SELECTION, WINDOW, 0);
	if(XGetSelectionOwner(DISPLAY, SELECTION) != WINDOW)
		return;
	
	while(1)
	{
		XNextEvent(DISPLAY, &event);
		switch(event.type)
		{
			case SelectionRequest:
				if(event.xselectionrequest.selection != SELCTION)
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
					r = XChangeProperty(xse.display, xse.requestor, xse.property, XA_STRING, 8, PropModeReplace, TEXT, SIZE);
				else if(xse.target == utf8)
					r = XChangeProperty(xse.display, xse.requestor, xse.property, utf8, 8, PropModeReplace, TEXT, SIZE);
				else
					xse.property = None;
				if((r & 2) == 0)
					XSendEvent(DISPLAY, xse.requestor, 0, 0, (XEvent*)&xse);
		}
	}
}

int main(int argc, char* argv[])
{
	X11_clipboard clipboard;
	clipboard.copy((unsigned char*)argv[1], strlen(argv[1]));
}