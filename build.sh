#!/bin/bash 
host=$1

echo $host > platform/src/host
cp ~/.ssh/id_rsa ./platform/src/
cp ~/.ssh/id_rsa.pub ./platform/src/

docker build -t dev platform
docker run -t dev
