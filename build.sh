#!/bin/bash 

./kill.sh

set -e

docker build -t dev platform
docker run --rm -v $(pwd)/platform/src:/opt/src -v $(pwd)/build:/opt/build -t dev
