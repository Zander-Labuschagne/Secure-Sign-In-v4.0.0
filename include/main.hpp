/**
 * Copyright (C) 2019 Zander Labuschagne. All rights reserved.
 * @version 4.0.0 05/04/19
 * @since 4.0.0
 *
 * Authors:
 *         @author Zander Labuschagne <zander.labuschagne@protonmail.ch>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU GPL 2.0 License, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GPL 2.0 License for more details.
 *
 * You should have received a copy of the GNU GPL 2.0 License
 * along with this program; if not, write to the author,
 * contact details above in line 7.
 */

 /**
 * Main Secure Sign In program (entry point).
 * @version 4.0.0
 * @since 4.0.0
 * g++: -lX11
*/

void print_help();
void display_password(const char *);
void copy_password(const char *);
void copy_password_linux(const char *);
void copy_password_macos(const char *);
void copy_password_windows(const char *);
