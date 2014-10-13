# fcs-platform

This is the platform support for my Raspberry Pi-based flight controller.

Hardware:
 
 - Raspberry Pi Model B (assumed to be running the Docker daemon)
 - Pololu Micro Maestro serial servo controller
 - CH Robotics UM-6 and Pololu GPS via Pololu USB-to-serial adapter
 
# TODO

 - Connect to and read from UM-6
 - Export C API for driving servos
 - Export C API for reading UM-6

# DONE

 - Get Rpi to wiggle a servo using Maestro example bash script
 - Get Docker on Rpi
 - Build minimal development container with compiler
 - Ship source code from laptop to Rpi
 - Compile and run source code within development container
 - Get Rpi to wiggle a servo using Maestro example C code

# Setup

Install Arch Linux on an SD card. Make sure to resize the partition to take up the available space. (Use `fdisk` to rewrite the partition table and `resize2fs` to do the actual resizing. Google it.)

Install Docker on the Rpi and start the Docker daemon such that it will listen on the local unix socket as well as over a TCP port:

    $ pacman -Syu
    $ pacman -S docker
    $ docker -d -H unix:///var/run/docker.sock -H 0.0.0.0:9000

On your laptop, set `DOCKER_HOST` to the Rpi's IP address.

    $ export DOCKER_HOST=tcp://192.168.2.200:9000
    
Build the Docker image in which the platform support will run:

    $ ./build.sh 

Assuming the setup went well, you should be able to edit the contents of `platform/src` and then deploy and run the program with:

    $ ./run.sh 192.168.2.200

# Notes about connecting to the Pi

I wanted to be able to work on the Pi without having to plug it into a router, rather, I wanted to plug it into my Macbook Air directly via ethernet and the Thunderbolt ethernet adapter. OS X Internet Sharing was being a contrarian as I attempted to do this. After much wailing and gnashing of teeth I arrived at this process:

 1. Disable Internet Sharing
 1. Delete the following files:
    `/Library/Preferences/SystemConfiguration/com.apple.nat.plist`
    `/Library/Preferences/SystemConfiguration/NetworkInterfaces.plist`
    `/Library/Preferences/SystemConfiguration/com.apple.network.identification.plist`
    `/Library/Preferences/SystemConfiguration/com.apple.airport.preferences.plist`
  1. Reboot.
  1. Re-enable Internet Sharing.
  1. It worked!
  
Create `/etc/bootptab` to cause the Pi to always get the same IP address:

    %%
    raspberry-pi 1 b8:27:eb:c:45:4f 192.168.2.200 

Do not go about trying to hand-edit `/etc/bootpd.plist`, because the Internet Sharing dialog in System Preferences is meant to stomp on that file. Tailing `/var/log/system.log` was instructive. 

I also modified `/System/Library/LaunchDaemons/bootps.plist` to add the `-dv` flag so `bootpd` would emit more interesting log messages:

    ...
    <key>ProgramArguments</key>
    <array>
        <string>/usr/libexec/bootpd</string>
        <string>-dv</string>
    </array>
    ....

