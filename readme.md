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
 - <strike>Get Docker on Rpi</strike> *dumb idea*
 - <strike>Build minimal development container with compiler</strike> *needed a cross-compiler instead*
 - Ship source code from laptop to Rpi
 - <strike>Compile and run source code within development container</strike> *going to run it natively*
 - Set up cross compiler
 - Cross-compile, deploy binary, and run on Rpi in one command
 - Get Rpi to wiggle a servo using Maestro example C code

# Setup

## Put Linux on Rpi

Install Arch Linux on an SD card. Make sure to resize the partition to take up the available space. (Use `fdisk` to rewrite the partition table and `resize2fs` to do the actual resizing. Google it.)

## Put Docker on laptop

Make sure you've got Docker on your laptop and your `docker` command is set up to talk to a Docker daemon.


## Build cross-compiler

We're going to build a Docker container with a cross-compiler in it. It will compile our source code on our laptop and then deploy and run the resulting binary on the Rpi. 

In order to achieve the deploy and run, the container will need to be able to log into your Rpi. I'm on OS X and using `boot2docker`. Sharing data on my local disk into the container using volumes is not possible on OS X right now. I've decided the least insane thing to do is to put my SSH keys into the container during the bootstrapping process. *trollface*

**DO NOT PUSH THE RESULTING DOCKER IMAGE TO A PUBLIC REPOSITORY! IT HAS YOUR PRIVATE KEY IN IT.**

    $ ./bootstrap root@192.168.2.200

Now you can compile and run the source:

    $ ./build.sh

Congratulations, you're hacking!

For some reason the program doesn’t always die on the Pi when you expect it to. You might need to:

    $ ssh root@192.168.2.200 killall fcs-platform

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

# Notes about talking to the GPS

TIL that this is useful for `cat`-ing the raw output from the GPS:

    $ stty -F /dev/ttyUSB0 57600 raw