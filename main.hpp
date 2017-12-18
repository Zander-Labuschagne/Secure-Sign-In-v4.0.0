#include "SecureSignIn.hpp"
#include <sstream>
#include <string>

void display_password(const char* password);
std::string exc(const char* cmd);
std::string copy_password(const char* password);

void display_password(const char* password)
{
	for(unsigned short xviii = 0; *(password + xviii) != '\0'; xviii++)
		std::cout << *(password + xviii);
	std::cout << std::endl;
}

std::string exec(const char* cmd)
{
	FILE* pipe = popen(cmd, "r");
	if (!pipe) 
		return "ERROR";
	char buffer[128];
	std::string result = "";
	while(!feof(pipe))
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	pclose(pipe);
	return result;
}

std::string copy_password(const char* password)
{
	unsigned short xvix;
	for(xvix = 0; *(password + xvix) != '\0'; xvix++);
	
	std::stringstream cmd;
	cmd << "echo \"" << password << "\" | pbcopy";
	return exec(cmd.str().c_str());
}