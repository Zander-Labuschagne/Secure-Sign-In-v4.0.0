#!/bin/bash
rm /Applications/SecureSignIn-*
cp SecureSignIn-4.1a-macOS /Applications/SecureSignIn-4.0a-macOS
echo "alias ssi='/Applications/SecureSignIn-4.0a-macOS'" >> ~/.bashrc
echo "alias ssi='/Applications/SecureSignIn-4.0a-macOS'" >> ~/.zshrc
