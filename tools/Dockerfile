#
# Cross compiler environment for raspberry pi
#
# For more information:
# http://stackoverflow.com/questions/19162072/installing-raspberry-pi-cross-compiler/19269715#19269715
# https://github.com/philipz/raspberry-pi-crosscompile
FROM ubuntu:14.04

RUN locale-gen en_US.UTF-8; update-locale LANG=en_US.UTF-8
RUN apt-get update && apt-get install -y git cmake make build-essential

# raspberry pi compiler tools
RUN mkdir -p /opt/rpi; cd /opt/rpi; git clone https://github.com/raspberrypi/tools.git
RUN echo "export PATH=$PATH:/opt/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin" > /root/.bashrc
ADD pi.cmake /opt/rpi/pi.cmake

ADD host /opt/rpi/host

RUN mkdir -p /root/.ssh
ADD id_rsa /root/.ssh/id_rsa
ADD id_rsa.pub /root/.ssh/id_rsa.pub

CMD ["/bin/bash"]