#!/bin/bash
set -e

python creghead.py gp9_regs.py > platform/gp9_regs.h

cd /opt/build
cmake -D CMAKE_TOOLCHAIN_FILE=/opt/rpi/pi.cmake /opt/src
make

