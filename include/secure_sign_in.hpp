/**
 * Copyright (C) 2019 Zander Labuschagne. All rights reserved.
 * @version 3.0.0 05/04/19
 * @since 3.0.0
 *
 * Authors:
 *         @author Zander Labuschagne <zander.labuschagne@protonmail.ch>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU GPL 3.0 License, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GPL 3.0 License for more details.
 *
 * You should have received a copy of the GNU GPL 3.0 License
 * along with this program; if not, write to the author,
 * contact details above in line 7.
 */

#ifndef SECURE_SIGN_IN_HPP
#define SECURE_SIGN_IN_HPP

/**
 * @brief Class containing encryption function(s) for the Secure Sign In applications
 * @since 3.0.0
 * secure_sign_in.hpp
*/
class SecureSignIn
{
public:
	SecureSignIn();
	char *encrypt(const char *, const char *, const unsigned short);
private:
	unsigned short get_length(const char *);
};

#endif // SECURE_SIGN_IN_HPP
