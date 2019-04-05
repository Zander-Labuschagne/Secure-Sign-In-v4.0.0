#!/bin/bash
rm /Applications/SecureSignIn-*
cp SecureSignIn-4.2a-macOS /Applications/SecureSignIn-4.2a-macOS
echo "alias ssi='/Applications/SecureSignIn-4.2a-macOS'" >> ~/.bashrc
echo "alias ssi='/Applications/SecureSignIn-4.2a-macOS'" >> ~/.zshrc
