#!/bin/bash 

./kill.sh

set -e

docker build -t dev platform
docker run -t dev
