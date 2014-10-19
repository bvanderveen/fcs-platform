#!/bin/bash 

set -e

docker build -t dev platform
docker run -t dev
