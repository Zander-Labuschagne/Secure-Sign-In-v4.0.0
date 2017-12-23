//gcc ... -lX11
#ifdef __linux__
	#include <string.h>
	#include <time.h>
	#include <X11/Xlib.h>

	class X11_clipboard
	{
	public:
		void copy(const char *text);
		char *paste();
	private:
		Display *display = XOpenDisplay(0);
		const int N = DefaultScreen(display);
		Window window = XCreateSimpleWindow(display, RootWindow(display, N), 0, 0, 1, 1, 0, BlackPixel(display, N), WhitePixel(display, N));
		XEvent event;
		const Atom ATOM_TARGETS = XInternAtom(display, "TARGETS", 0);
		Atom UTF8 = XInternAtom(display, "UTF8_STRING", true);
		const Atom XA_STRING = 31;
		const Atom SELECTION = XInternAtom(display, "CLIPBOARD", 0);
	};
#endif