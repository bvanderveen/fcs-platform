#
# Cross compiler environment for raspberry pi
#
# Follows this stack overflow article
# http://stackoverflow.com/questions/19162072/installing-raspberry-pi-cross-compiler/19269715#19269715
#
FROM ubuntu:14.04
MAINTAINER Philipz <philipzheng@gmail.com>

RUN locale-gen en_US.UTF-8
RUN update-locale LANG=en_US.UTF-8


# standard base
RUN apt-get -qq update && DEBIAN_FRONTEND=noninteractive apt-get install -y -q dialog net-tools lynx wget vim-tiny nano git curl sudo zip

# build tools
# we need to install a dummy libfuse or docker will fail
#RUN apt-get install libfuse2
#RUN cd /tmp ; apt-get download fuse
#RUN cd /tmp ; dpkg-deb -x fuse_* .
#RUN cd /tmp ; dpkg-deb -e fuse_*
#RUN cd /tmp ; rm fuse_*.deb
#RUN cd /tmp ; echo -en '#!/bin/bash\nexit 0\n' > DEBIAN/postinst
#RUN cd /tmp ; dpkg-deb -b . /fuse.deb
#RUN cd /tmp ; dpkg -i /fuse.deb
#RUN dpkg --add-architecture i386
#RUN echo "deb http://old-releases.ubuntu.com/ubuntu/ raring main restricted universe multiverse" > /etc/apt/sources.list.d/ia32-libs-raring.list
#RUN apt-get -qq update && DEBIAN_FRONTEND=noninteractive apt-get install -y -q cmake make ia32-libs

# raspberry pi compiler tools
RUN mkdir -p /opt/rpi; cd /opt/rpi; git clone https://github.com/raspberrypi/tools.git
RUN echo "export PATH=$PATH:/opt/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin" > /root/.bashrc
ADD pi.cmake /opt/rpi/pi.cmake

RUN apt-get install -y cmake make 

# Download cmake hello world to verify that we can compile for pi
# Copy CMakeHelloWorld to your pi and test that it runs
RUN cd /opt/rpi; git clone https://github.com/jameskbride/cmake-hello-world.git; cd cmake-hello-world; mkdir build
RUN cd /opt/rpi/cmake-hello-world/build; cmake -D CMAKE_TOOLCHAIN_FILE=/opt/rpi/pi.cmake ../; make

# Also include sample opencv build script
#ADD build.opencv /root/build.opencv

# Volume
#VOLUME /data 

CMD ["/bin/bash"]