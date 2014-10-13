host=$1

# send over the source code
ssh -At root@$host "rm -rf /root/src; mkdir /root/src"
scp -r ./platform/src root@$host:/root

# compile and run it
ssh -At root@$host "docker run --rm --device=/dev/ttyACM0:/dev/ttyACM0 -v /root/src:/home/src -t dev make run"