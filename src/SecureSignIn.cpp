//Exception handling?
//Moet ek soos die pointers gebruik? Of arrays? of vectors?
//Benchmark die verskillende implementyerings

#include <iostream>

#include "../include/SecureSignIn.hpp"

/*
 * Class containing encryption function(s) for the Secure Sign In application
 * 
 * Author:
 *	Zander Labuschagne <zander.labuschagne@protonmail.ch>
 *
 * I am still learning C++ so if anything is unacceptable or a violation to some standards please inform me.
 * TODO: Experiment with vectors
*/

/*
* Function to encrypt text, used for the encryption of passwords in the Secure Sign In application.
* user_password contains plain text password to be encrypted.
* key contains the key entered by the user, could be anything, even the password.
* limit specifies the limit of the password length, some websites have limitations on the password length.
* returns an encrypted password that should be more complex and appears random.
*/
char* SecureSignIn::encrypt(const char *user_password, const char *key, unsigned short limit)
{
	char *system_password;
	system_password = (char*)malloc(256);
	unsigned short key_index = 0;
	unsigned short i = 0;
	char *spec_chars;
	spec_chars = (char*)malloc(256);
	unsigned short ii = 0;
	unsigned short pos = 0;
	unsigned short spec_char_count = 0;


	//for(char t : user_password)
	unsigned short password_length = 0;
	for (char t = *user_password; t != '\0'; t = *(user_password + ++password_length)) {
		if (t >= 65 && t <= 90) { //Encrypting uppercase characters
			short temp = t - 65 + (*(key + key_index) - 65);
			if (temp < 0)
				temp += 26;
			if (temp <= 0)
				temp += 26;

			*(system_password + i++) = (char)(65 + (temp % 26));
			//if(++key_index == key.length)
			if (*(key + ++key_index) == '\0')
				key_index = 0;
		} else if (t >= 97 && t <= 122) { //Encrypting lowercase characters
			short temp = t - 97 + (*(key + key_index) - 97);
			if(temp < 0)
				temp += 26;
			if(temp < 0)
				temp += 26;

			*(system_password + i++) = (char)(97 + (temp % 26));
			//if(++key_index == key.length)
			if(*(key + ++key_index) == '\0')
				key_index = 0;
		} else { //Encrypting special characters

			*(spec_chars + ii++) = (char)(pos + 65);
			*(spec_chars + ii++) = t;
			spec_char_count++;
		}
		pos++;
	}

	char *final_password;
	final_password = (char*)malloc(256);
	i = 0;
	*(final_password + i++) = (char)(spec_char_count == 0 ? 65 : (--spec_char_count + 65)); //Encrypting the number of special characters
	for (char t = *spec_chars; t != '\0'; i++, t = *(spec_chars + i - 1)) //Encrypting special characters and positions of special characters
		*(final_password + i) = t;
	ii = i;
	for (char t = *system_password; t != '\0'; i++, t = *(system_password + i - ii)) //Adding the encrypted password to the encrypted special characters and positions
		*(final_password + i) = t;

	free(system_password);
	free(spec_chars);

	short ext = -1;
	if (i > 32 && limit > 12)
		while (1) {
			std::cout << "Warning: Password is longer than 32 characters" << std::endl << "Would you like to shorten the password to the 32 limit? (y/n)" << std::endl;
			std::string input;
			std::cin >> input;
			if (toupper(input[0]) == 'Y') {
				ext = 1;
				break;
			} else if (toupper(input[0]) == 'N') {
				break;
			}
			std::cout << "You have entered an inapropriate answer given the issue. Please try again.";
		}

	unsigned short length;
	for (length = 0; *(final_password + length) != '\0'; ++length);//Die maak die password so klein as moontlik(geen null characters aan die einde) -> kan ek die bypass omdat dit C++ pointers is?
	char* cipher_password;
	cipher_password = (char*)malloc(length);
	for (unsigned short xi = 0; xi < length /*&& xi < cipher_password.length*/ ; ++xi)
		*(cipher_password + xi) = *(final_password + xi);

	free(final_password);	

	//Suffle password for extra security
	char *evens; //Kan dalk vectors ook gebruik
	evens = (char*)malloc(256);
	char *odds;
	odds = (char*)malloc(256);
	unsigned short xii = 0, xiii = 0;
	for (unsigned short iii = 0; iii < length; ++iii)
		if ((unsigned short)(*(cipher_password + iii) % 2 == 0))
			*(evens + xii++) = *(cipher_password + iii);
		else
			*(odds + xiii++) = *(cipher_password + iii);
	char *odds_reversed;
	odds_reversed = (char*)malloc(xiii);
	for (unsigned short xvi = 0, xvii = xiii; xvii > 0; xvii--, ++xvi) //Reverse odds, like stack
		*(odds_reversed + xvi) = *(odds + xvii - 1);
	free(odds);

	unsigned short iv = 0;
	unsigned short xiv = 0;
	unsigned short xv = 0;
	while (xii > 0 || xiii > 0) { //Obfuscation
		if (xiii > 0) {
			*(cipher_password + iv++) = *(odds_reversed + xiv++);
			xiii--;
		}
		if (xii > 0) {
			*(cipher_password + iv++) = *(evens + xv++);
			xii--;
		}
	}

	free(odds_reversed);
	free(evens);

	//Encrypt special chars further
	for (unsigned short v = 0; v < length/*cipher_password.lerngth*/; ++v)
		if ((unsigned short)(*(cipher_password + v)) <= 47) {
			*(cipher_password + v) += 10;
		} else if ((unsigned short)(*(cipher_password + v)) > 47 && (unsigned short)(*(cipher_password + v)) < 64) {
			*(cipher_password + v) -= 5;
		} else if ((unsigned short)(*(cipher_password + v)) > 90 && (unsigned short)(*(cipher_password + v)) <= 96) {
			if(length % 2 == 0)
				*(cipher_password + v) += 2;
			else
				*(cipher_password + v) -= 2;
		}

	//Replacing unloved characters
	for (unsigned short vi = 0; vi < length; ++vi) //As ek length so gaan gebruik moet hy const word
		if ((unsigned short)(*(cipher_password + vi)) == 34)
			*(cipher_password + vi) = 123;
		else if ((unsigned short)(*(cipher_password + vi)) == 38)
			*(cipher_password + vi) = 124;
		else if ((unsigned short)(*(cipher_password + vi)) == 60)
			*(cipher_password + vi) = 125;
		else if ((unsigned short)(*(cipher_password + vi)) == 62)
			*(cipher_password + vi) = 126;

	//Limitations
	if(ext == 1 || limit < 32) {
		char* cipher_password_limited = (char*)malloc(length);
		for(unsigned short vii = 0; vii < length && vii < limit; ++vii)
			*(cipher_password_limited + vii) = *(cipher_password + vii);

		return cipher_password_limited; //TODO:Check
	}

	return cipher_password;
}