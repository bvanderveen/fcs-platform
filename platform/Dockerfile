FROM ubuntu:14.04

RUN locale-gen en_US.UTF-8; update-locale LANG=en_US.UTF-8
RUN apt-get update && apt-get install -y git cmake make build-essential python

RUN mkdir -p /opt/rpi-tools
RUN mkdir /opt/src
RUN mkdir /opt/build

WORKDIR /opt/src

CMD ./build.sh