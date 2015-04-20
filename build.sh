#!/bin/bash 

set -e

docker build -t compiler compiler
docker run --rm -v $(pwd):/opt -v $(pwd)/deps/rpi-tools:/opt/rpi-tools -t compiler
