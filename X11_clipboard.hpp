//g++ ... -lX11

#include <X11/Xlib.h>
#include <string.h>

class X11_clipboard
{
	private:
		const Display* DISPLAY = XOpenDisplay(0);
		const int N = DefaultScreen(DISPLAY);
		const Window WINDOW = XCreateSimpleWindow(DISPLAY, RootWindow(DISPLAY, N), 0, 0, 1, 1, 0, BlackPixel(DISPLAY, N), WhitePixel(DISPLAY, N));
		const Atom TARGETS_ATOM = XInternAtom(DISPLAY,"TARGETS", 0);
		const Atom TEXT_ATOM = XInternAtom(DISPLAY, "TEXT", 0);
		Atom utf8 = XInternAtom(DISPLAY, "UTF8_STRING", 1);
		const Atom XA_ATOM = 4;
		const Atom XA_STRING = 31;
		const Atom SELECTION = XInternAtom(DISPLAY, "CLIPBOARD", 0);
		char* paste_type(Atom atom);
		
	public:
		void copy(const Atom selection, const unsigned char* text, const int size);
		char* paste();
};