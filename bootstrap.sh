#!/bin/bash

# i'm using boot2docker. the least insane thing to do is to put the keys into 
# the build+deploy container so we can deploy from there.

set -e

host=$1

if [[ -z "$host" ]]; then
	echo "you must specify a raspberry pi host (e.g., root@192.168.2.200)"
	exit -1
fi

scp ~/.ssh/id_rsa.pub $host:/root/.ssh/authorized_keys

echo $host > ./tools/host

cp ~/.ssh/id_rsa ./tools
cp ~/.ssh/id_rsa.pub ./tools

docker build -t rpi-cross-compiler tools