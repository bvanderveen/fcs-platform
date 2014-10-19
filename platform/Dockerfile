FROM rpi-crosscompiler
RUN mkdir /opt/sources
RUN apt-get install -y build-essential
ADD src/ /opt/sources
RUN ls -al /opt/sources
RUN mkdir /root/.ssh; cp /opt/sources/id_rsa /root/.ssh/id_rsa
WORKDIR /opt/sources
CMD ./build-platform.sh