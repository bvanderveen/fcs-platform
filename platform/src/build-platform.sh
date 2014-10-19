#!/bin/bash

set -e
host="$(cat /opt/rpi/host)"
mkdir build
cd build
cmake -D CMAKE_TOOLCHAIN_FILE=/opt/rpi/pi.cmake ../
make
scp -oStrictHostKeyChecking=no platform/fcs-platform $host:/home/fcs-platform
ssh -t $host /home/fcs-platform
