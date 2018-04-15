#include <string>

#if defined (__MACH__) || defined(__linux__)
	#include <termios.h>
#endif

/*
 * class containing functions to allow interaction with tty session on UNIX systems
 *
 * Author:
 *	Zander Labuschagne <zander.labuschagne@protonmail.ch>
 *
 * This should only be compatible with UNIX-like systems, if not please inform me.
 * I am still learning C++ so if anything is unacceptable or a violation to some standards please inform me.
*/

class TTY
{
public:
	std::string execute_command(const char *);
	void set_echo(bool);
	void set_buffer(bool);

private:
	struct termios tty;
	void set_echo_unix(bool);
	void set_echo_windows(bool);
	void set_buffer_unix(bool);
	void set_buffer_windows(bool);
};