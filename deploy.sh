#!/bin/bash
set -e

host=$1

if [[ -z "$host" ]]; then
	echo "you must specify a raspberry pi host (e.g., root@192.168.2.200)"
	exit -1
fi

./kill.sh

#scp -oStrictHostKeyChecking=no build/chr-um6/tests/um6_hardware_test $host:/home/um6_hardware_test
#ssh -t $host /home/um6_hardware_test

scp -oStrictHostKeyChecking=no build/platform/fcs-platform $host:/home/fcs-platform
ssh -t $host /home/fcs-platform