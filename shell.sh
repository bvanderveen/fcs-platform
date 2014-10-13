host=$1
ssh -At root@$host "docker run --rm -i --device=/dev/ttyACM0:/dev/ttyACM0 -t dev /bin/bash"