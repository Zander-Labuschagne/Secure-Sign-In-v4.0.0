#!/bin/bash

mkdir /opt/Cryogen
rm /opt/Cryogen/SecureSignIn-*
rm /usr/bin/ssi
cp SecureSignIn-4.1a-linux /opt/Cryogen/
touch /usr/bin/ssi
echo "#!/bin/bash" > /usr/bin/ssi
echo "/opt/Cryogen/SecureSignIn-4.1a-linux" > /usr/bin/ssi
chmod +x /usr/bin/ssi
