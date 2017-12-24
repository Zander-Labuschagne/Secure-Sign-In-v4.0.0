#!/bin/bash

mkdir /opt/Cryogen
cp SecureSignIn-4.0a-linux /opt/Cryogen/
touch /usr/bin/ssi
echo "#!/bin/bash" > /usr/bin/ssi
echo "/opt/Cryogen/SecureSignIn-4.0a-linux" > /usr/bin/ssi
chmod +x /usr/bin/ssi
