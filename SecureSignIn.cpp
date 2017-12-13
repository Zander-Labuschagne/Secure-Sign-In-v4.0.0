//Exception handling?
//Is die while(1) aanvaarbaar?
//length van array as pointer
//kan char na unsigned short cast?
//is dir nodig om te cast?
//Moet ek soos die pointers gebruik? Of arrays? of vectors?
//Indien arrays... new array of net skoon?
//Benchmark die verskillende implementyerings
#include "SecureSignIn.hpp"

SecureSignIn::SecureSignIn()
{

}

char* SecureSignIn::encrypt(const char* user_password, const char* key, const unsigned short limit)
{
	char* system_password;
	unsigned short key_index = 0;
	unsigned short i = 0;
	char* spec_chars;
	unsigned short ii = 0;
	unsigned short pos = 0;
	unsigned short spec_char_count = 0;
	char* final_password;

	for(char t : user_password)
	{
		if(t >= 65 && t <= 90) //Encrypting uppercase characters
		{
			unsigned short temp = t - 65 + (*(key + key_index) - 65);
			if(temp < 0)
				temp += 26;
			if(temp <= 0)
				temp += 26;

			*(system_password + i++) = (char)(65 + (temp % 26));
			if(++key_index == key.length)
				key_index = 0;
		}
		else if(t >= 97 && t <= 122) //Encrypting lowercase characters
		{
			unsigned short temp = t - 97 + (*(key + key_index) - 97);
			if(temp < 0)
				temp += 26;
			if(temp < 0)
				temp += 26;

			*(system_password + i++) = (char)(97 + (temp % 26));
			if(++key_index == key.length)
				key_index = 0;
		}
		else //Encrypting special characters
		{
			*(spec_chars + ii++) = (char)(pos + 65);
			*(spec_chars + ii++) = t;
			spec_char_count++;
		}
		pos++;
	}
	i = 0;
	*(final_password + i++) = (char)(spec_char_count == 0 ? 65 : (--spec_char_count + 65)); //Encrypting the number of special characters
	for(char t = *spec_chars; t != 0; i++, t = *(spec_chars + i - 1)) //Encrypting special characters and positions of special characters
		*(final_password + i) = t;
	ii = i;
	for(char t = *system_password; t != 0; i++, t = *(system_password + i - ii))
		*(final_password + i) = t;

	short ext = -1;
	if(i > 32)
	{
		while(1) //Is die aanvaarbaar?
		{
			std::cout << "Warning: Password is longer than 32 characters" << std::endl << "Would you like to shorten the password to the 32 limit? (y/n)" << std::endl;
			std::string input;
			std::cin >> input;
			if(input == "yes" || input == "y")
			{
				ext = 1;
				break;
			}
			else if(input == "no" || input == "n")
				break;
			std::cout << "You have entered an inapropriate answer given the issue. Please try again.";
		}
		
	}

	unsigned short length = 0;
	for(unsigned short x = 0; *(final_password + x) != '\0'; x++)
		length++; //Die maak die password so klein as moontlik(geen null characters aan die einde) -> kan ek die bypass omdat dit C++ pointers is?
	char* cipher_password;
	for(unsigned short xi = 0; xi < length /*&& xi < cipher_password.length*/ ; xi++)
		*(cipher_password + xi) = *(final_password + xi);

	//Suffle password for extra security
	char* evens; //Kan dalk vectors ook gebruik
	char* odds;
	unsigned short xii = 0, xiii = 0;
	for(unsigned short iii = 0; iii < /*cipher_password.length*/ length; iii++)
		if((unsigned short)(*(cipher_password + iii) % 2 == 0))
			*(evens + xii++) = *(cipher_password + iii);
		else
			*(odds + xiii++) = *(cipher_password + iii);
	unsigned short iv = 0;
	while(xii >= 0 || xiii >= 0) //Obfuscation
	{
		unsigned short xiv = 0;
		unsigned short xv = 0;
		if(xiii >= 0)
		{
			*(cipher_password + iv++) = *(odds + xiv++);
			xiii--;
		}
		if(xii >= 0)
		{
			*(cipher_password + iv++) = *(evens + xv++);
			xii--;
		}
	}

	//Encrypt special chars further
	for(unsigned short v = 0; v < length/*cipher_password.lerngth*/; v++)
		if((unsigned short)(*(cipher_password + v)) <= 47)
			*(cipher_password + v) += 10;
		else if((unsigned short)(*(cipher_password + v)) > 47 && (unsigned short)(*(cipher_password + v)) < 64)
			*(cipher_password + v) -= 5;
		else if((unsigned short)(*(cipher_password + v)) > 90 && (unsigned short)(*(cipher_password + v)) <= 96)
			if(length % 2 == 0)
				*(cipher_password + v) += 2;
			else
				*(cipher_password + v) -= 2;

	//Replacing unloved characters
	for(unsigned short vi = 0; vi < length; vi++) //As ek length so gaan gebruik moet hy const word
		if((unsigned short)(*(cipher_password + vi)) == 34)
			*(cipher_password + vi) = 123;
		else if((unsigned short)(*(cipher_password + vi)) == 38)
			*(cipher_password + vi) = 124;
		else if((unsigned short)(*(cipher_password + vi)) == 60)
			*(cipher_password + vi) = 125;
		else if((unsigned short)(*(cipher_password + vi)) == 62)
			*(cipher_password + vi) = 126;

	//Limitations
		if(ext == 1 || limit < 32)
		{
			char* cipher_password_limited;
			for(unsigned short vii = 0; vii < length && vii < limit; vii++)
				*(cipher_password_limited + vii) = *(cipher_password + vii);

			return cipher_password_limited; //Check
		}

		return cipher_password;
}

SecureSignIn::~SecureSignIn()
{

}