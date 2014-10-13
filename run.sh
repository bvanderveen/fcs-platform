host=$1

ssh -At root@$host "rm -rf /root/src; mkdir /root/src"
scp -r ./platform/src root@$host:/root
ssh -At root@$host "docker run --rm --device=/dev/ttyACM0:/dev/ttyACM0 -v /root/src:/home/src -t dev make run"