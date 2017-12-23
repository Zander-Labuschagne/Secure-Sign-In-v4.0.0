#include "TTY.hpp"

std::string TTY::execute_command(const char *tty)
{
	FILE* pipe = popen(tty, "r");
	if (!pipe) 
		return "ERROR";

	char buffer[128];
	std::string result = "";
	while (!feof(pipe))
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	pclose(pipe);
	
	return result;
}

void TTY::set_echo(bool enabled = true)
{
	#if defined(__MACH__) || defined(__linux__)
		set_echo_unix(enabled);
	#elif _WIN32
		set_echo_windows(enabled);
	#endif
}

void TTY::set_buffer(bool enabled)
{
	#if defined(__MACH__) || defined(__linux__)
		set_buffer_unix(enabled);
	#elif _WIN32
		set_buffer_windows(enabled);
	#endif
}

#if defined(__MACH__) || defined(__linux__) //Inlcudes Apple(macOS, iOS), UNIX
	void TTY::set_echo_unix(bool enabled = true)
	{
		tcgetattr(STDIN_FILENO, &tty);
		
		if(!enabled)
			tty.c_lflag &= ~ECHO;
		else
			tty.c_lflag |= ECHO;

		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
	}
	
#elif _WIN32
	void TTY::set_echo_windows(bool enabled = true) //TODO: Test
	{
		HANDLE std_handle = GetStdHandle(STD_INPUT_HANDLE); 
		DWORD mode;
		GetConsoleMode(std_handle, &mode);

		if(!enabled)
			mode &= ~ENABLE_ECHO_INPUT;
		else
			mode |= ENABLE_ECHO_INPUT;

		SetConsoleMode(std_handle, mode);
	}
#endif

#if defined(__MACH__) || defined(__linux__)  //Inlcudes Apple(macOS, iOS), Linux, UNIX
	void TTY::set_buffer_unix(bool enabled)
	{
		tcgetattr(STDIN_FILENO, &tty); //get the current terminal I/O structure
		
		if (!enabled)
			tty.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
		else
			tty.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
				
		tcsetattr(STDIN_FILENO, TCSANOW, &tty); //Apply the new settings
	}

#elif _WIN32
	void TTY::set_buffer_windows(bool enabled)
	{
		set_buffer_posix(enabled); //TODO: Review this
	}
#endif
