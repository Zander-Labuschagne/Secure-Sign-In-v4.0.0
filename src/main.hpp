#include "SecureSignIn.hpp"
#include "TTY.hpp"
#ifdef __linux__
	#include "X11_clipboard.hpp"
#endif

void display_password(const char *password);
void copy_password(const char *password);
void copy_password_linux(const char *password);
void copy_password_macos(const char *password);
void copy_password_windows(const char *password);
