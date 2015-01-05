#!/bin/bash
set -e

host="$(cat ./host)"

#scp -oStrictHostKeyChecking=no build/chr-um6/tests/um6_hardware_test $host:/home/um6_hardware_test
#ssh -t $host /home/um6_hardware_test

scp -oStrictHostKeyChecking=no build/platform/fcs-platform $host:/home/fcs-platform
ssh -t $host /home/fcs-platform