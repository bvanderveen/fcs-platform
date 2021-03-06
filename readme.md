# fcs-platform

This is the platform support for my Raspberry Pi-based flight controller.

Hardware:
 
 - Raspberry Pi Model B 
 - Pololu Micro Maestro serial servo controller
 - CH Robotics <strike>UM-6 and Pololu GPS</strike> GP-9 via Pololu USB-to-serial adapter
 
# TODO

 - Get CMake to export a statically linkable library
 - Delete `main.c`
 - Get sending commands to the IMU to work properly
 - Get IMU health report to be more meaningful (ensure has GPS lock at least)
 - Write some kind of tests

# DONE

 - Add Rpi tools repository as a submodule rather than cloning it into toolchain Docker image
 - Connect to and read from IMU
 - Create C API for driving servos
 - Create C API for reading IMU
 - Get Rpi to wiggle a servo using Maestro example bash script
 - Ship source code from laptop to Rpi
 - Set up cross compiler
 - Cross-compile, deploy binary, and run on Rpi in one command
 - Get Rpi to wiggle a servo using Maestro example C code
 - Bring `platform/src` to root
 - Move `src/maestro` to `src/platform/servo_controller`
 
# MISTAKES

 - <strike>Get Docker on Rpi</strike> *dumb idea*
 - <strike>Build minimal development container with compiler</strike> *needed a cross-compiler instead*
 - <strike>Compile and run source code within development container</strike> *run a binary on the Rpi natively*

# Setup

## Put Linux on Rpi

Install Arch Linux on an SD card. Make sure to resize the partition to take up the available space. (Use `fdisk` to rewrite the partition table and `resize2fs` to do the actual resizing. Google it.)

## Put Docker on your laptop

Make sure you've got Docker on your laptop and your `docker` command is set up to talk to a Docker daemon. On OS X, I use `boot2docker`. Ensure `boot2docker` is up and running;

    $ boot2docker up

## Use the cross-compiler

The core build script builds a Docker container with a compiler toolchain that targets the Rpi and then invokes compiler.

    $ ./build.sh

The first time you run this it will take a while to build the docker image. Successive runs will be faster. 

## Run the program

We `scp` the resulting binary onto the Rpi (make sure your public key is on the Rpi so you don't have to type your password) and then run it.

    ./deploy.sh root@192.168.2.200

Congratulations, you're hacking!

For some reason the program doesn’t always die on the Pi when you expect it to. You might need to:

    $ ssh root@192.168.2.200 killall fcs-platform

# Notes about connecting to the Pi on OS X

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