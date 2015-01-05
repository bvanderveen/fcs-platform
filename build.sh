#!/bin/bash 

./kill.sh

set -e

docker build -t dev platform
docker run --rm -v $(pwd)/platform/src:/opt/src -v $(pwd)/build:/opt/build -v $(pwd)/rpi-tools:/opt/rpi-tools -t dev
