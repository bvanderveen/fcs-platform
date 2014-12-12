#!/bin/bash

set -e
mkdir build
cd build
cmake -D CMAKE_TOOLCHAIN_FILE=/opt/rpi/pi.cmake ../
make

