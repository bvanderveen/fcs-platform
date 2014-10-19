#!/bin/bash

set -e
host="$(cat /opt/rpi/host)"
mkdir build
cd build
cmake -D CMAKE_TOOLCHAIN_FILE=/opt/rpi/pi.cmake ../
make
scp -oStrictHostKeyChecking=no platform/fcs-platform $host:/home/fcs-platform
scp -oStrictHostKeyChecking=no chr-um6/tests/um6_hardware_test $host:/home/um6_hardware_test
ssh -t $host /home/um6_hardware_test
ssh -t $host /home/fcs-platform

