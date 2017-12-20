#include <X11/Xlib.h>
#include <string.h>

class X11_clipboard
{
	private:
		Display* display;
		Window window;
		Atom targets_atom;
		Atom text_atom;
		Atom utf8;
		const Atom XA_ATOM = 4;
		const Atom XA_STRING = 31;
		char* paste_type(Atom atom);
		
	public:
		void copy(const Atom selection, const unsigned char* text, const int size);
		char* paste();
};