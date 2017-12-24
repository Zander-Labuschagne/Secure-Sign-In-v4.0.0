# SecureSignIn v4a
This is a C++ CLI application I have created in an attempt to improve my online account security. The _a_ in the version code states that this is the CLI(Command Line Interface) version where _b_ would be the GUI(Graphical User Interface). Find the GUI version at https://github.com/Zander-Labuschagne/Secure-Sign-In-v4b

Benifits:
  - Remember one password for all sites, but all sites have different passwords.
  - Don't know the actual password which is entered in the password box on the website.
  - Provides a very strong, long and complex password.
  - No passwords are stored in file or database.
  - Easy to use.
  
This is my first official C++ application, feel free to criticize or comment. I would appreciate criticizem or comments on my coding style since I am not completely sure on the normal conventions, I tried to stick with the Linux kernel style.
There are Android, iPhone, iPad and macOS applications available as well, however they are not always up to date and I have left some of them discontinued/incomplete. I work on these projects in my free time only so don't expect regular updates from me.

macOS(Swift) version: TBA

Android version: TBA

iOS(iPhone) version: TBA

iOS(iPad) version: TBA

E-Mail: <zander.labuschagne@protonmail.ch>
Copyright (C) 2017 Zander Labuschagne. This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License version 3 as published by the Free Software Foundation.

How to install:

1.1. Linux: Either run the SecureSignIn-4.0a-linux file on a Linux operating system with the ``./SecureSignIn-4.0a-linux`` command or run the install.sh file after extracting the zip file to install the application on Linux systems with the following command: ``sudo sh install.sh`` which should add a ``ssi`` command that you can execute in a terminal session.
  
1.2. macOS: Either run the SecureSignIn-4.0a-macOS file on a macOS operating system with the ``./SecureSignIn-4.0a-macOS`` command or run the install.sh file after extracting the zip file to install the application on macOS systems with the following command: ``sudo sh install.sh`` which should add a ``ssi`` command that you can execute in a terminal session.
  
2. On some Linux and macOS systems it's necessary to run ``sudo chmod +x install.sh`` before installation.
  (Feel free to create a Windows version, I will eventaually do it myself when I get to it)

How to use application:
  
  1. Enter a password you will remember at the password prompt, preferably a strong and complicated password because this will influence the complexity of the resulting password.
  
  2. Enter a key, such as twitter, vimeo or whatever at the next prompt.
  
  3.1. Enter ``s`` to use a shorter version of the password (Some web services have a shorter limit on the password length).
  
  3.2. Enter ``l`` to use the default long version of the password.
  
  3.3. Enter ``q`` to exit immediately.
  
  4.1. Enter ``c`` to copy the password to memory, caution this will only last for 8 seconds until the password is cleared from memory. Paste the password in the password box on the website you are signing into.
  
  4.2. Enter ``v`` to view the password if you need to type it over manually.
  
  4.3. Enter ``q`` to exit immediately.
