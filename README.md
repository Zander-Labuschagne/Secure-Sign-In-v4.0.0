# Secure Sign In v4a
This is a C++ CLI application I have created in an attempt to improve my online account security. The _a_ in the version code states that this is the CLI(Command Line Interface) version where _b_ would be the GUI(Graphical User Interface). Find the GUI version at https://gitlab.com/Zander-Labuschagne/SecureSignIn-v4b or https://github.com/Zander-Labuschagne/SecureSignIn-v4b

### Benefits:
  - Remember one password for all sites, but all sites have different passwords.
  - Don't know the actual password which is entered in the password box on the website.
  - Provides a very strong, long and complex password.
  - No passwords are stored in file or database.
  - Easy to use.
  
This is my first official C++ application, feel free to criticize or comment. I would appreciate criticism or comments on my coding style since I am not completely sure on the normal conventions, I have tried to stick with the Linux kernel coding style (https://github.com/torvalds/linux/blob/master/Documentation/process/coding-style.rst).
There are Android, iPhone, iPad and macOS applications available as well, however they are not always up to date and I have left some of them discontinued/incomplete. I work on these projects in my free time only so don't expect regular updates from me. This is only compatible on Linux and macOS systems. (There is Windows compatible code that is supposed to be the equivalent but I have not tested it yet and some are not fully implemented yet)

macOS(Swift) version: TBA

Android version: TBA

iOS(iPhone) version: TBA

iOS(iPad) version: TBA

E-Mail: <zander.labuschagne@protonmail.ch>
Copyright (C) 2017 Zander Labuschagne. This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License version 3 as published by the Free Software Foundation.

## How to install:
### Linux:
Either run the SecureSignIn-4.1a-linux file on a Linux operating system with the ``./SecureSignIn-4.1a-linux`` command or run the install.sh file after extracting the zip file to install the application on Linux systems with the following command: ``sudo sh install.sh`` which should add a ``ssi`` command that you can execute in a terminal session.
### macOS:
Either run the SecureSignIn-4.1a-macOS file on a macOS operating system with the ``./SecureSignIn-4.1a-macOS`` command or run the install.sh file after extracting the zip file to install the application on macOS systems with the following command: ``sh install.sh`` which should add a ``ssi`` command that you can execute in a terminal session.
  
_On some Linux and macOS systems it's necessary to run ``sudo chmod +x install.sh`` before installation.
  (Feel free to create a Windows version, I will eventually do it myself when I get to it)_

## How to use application:

1. Run the application in terminal with the command ``ssi``.
    * Optional arguments may be added to the command such as ``ssi -l -c`` or ``ssi -lc`` which is handy if you already know what you want to do and prefer not to be prompted by the application each time resulting in a quicker interaction and immediate result.
        
    **Optional arguments:**
        
        * ``-l``, ``--long``	The resulting password will be the default long version.
	    * ``-s``, ``--short``	The resulting password will be a shortened version of the original default password.
	    * ``-c``, ``--copy``	The resulting password will be copied to memory for a few seconds after which it will be removed from memory.
	    * ``-v``, ``--verbose``	The resulting password will be displayed on the terminal screen if needed to type over manually (not safe -- only use when absolutely necessary).
	    * ``-h``, ``--help``	Displays the help menu.
2. Enter a password you will remember at the password prompt, preferably a strong and complicated password because this will influence the complexity of the resulting password.
3. Enter a key, such as twitter, vimeo or whatever at the next prompt.
4. Choose one of the options below:
    * Enter ``s`` to use a shorter version of the password (Some web services have a shorter limit on the password length).
    * Enter ``l`` to use the default long version of the password.
    * Enter ``q`` to exit immediately.
5. Choose one of the options below:
    * Enter ``c`` to copy the password to memory, caution this will only last for 8 seconds until the password is cleared from memory. Paste the password in the password box on the website you are signing into.
    * Enter ``v`` to view the password if you need to type it over manually (not safe -- only use when absolutely necessary).
    * Enter ``q`` to exit immediately.
