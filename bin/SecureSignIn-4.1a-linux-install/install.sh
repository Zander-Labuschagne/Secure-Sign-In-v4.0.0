#!/bin/bash

if [ -f /usr/bin/ssi ]; then
	rm /usr/bin/ssi
	echo "A version of Secure Sign In detected and removed."
fi
cp SecureSignIn-4.1a-linux /usr/bin/ssi
chmod +x /usr/bin/ssi
echo "Secure Sign In v4.1.1a successfully installed."
