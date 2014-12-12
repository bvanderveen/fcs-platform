#include "gps.h"
#include <stdio.h>  
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void writeResetToDefaults(int fd) {
    unsigned char command[] = "$PMTK104*37\r\n";
    if (write(fd, command, sizeof(command)) == -1)
    {
        printf("error writing\n");
        perror("perror writing");
    }
}

void writeVersionQuery(int fd) {
    unsigned char query[] = "$PMTK605*6D\r\n";
    if (write(fd, query, sizeof(query)) == -1)
    {
        printf("error writing\n");
        perror("perror writing");
    }
}
void writeACK(int fd) {
    unsigned char ack[]= "$PMTK001,101,0*33\r\n";
    if (write(fd, ack, sizeof(ack)) == -1)
    {
        printf("error writing\n");
        perror("perror writing");
    }
}

void resetNMEASettings(int fd) {
    unsigned char ack[]= "$PMTK314,-1*04\r\n";
    if (write(fd, ack, sizeof(ack)) == -1)
    {
        printf("error writing\n");
        perror("perror writing");
    }
}

void talkToGPS() {
    printf("Let's talk to GPS!\n");

    const char * device = "/dev/ttyUSB0";  // Linux
    int fd = open(device, O_RDWR | O_NOCTTY);
    if (fd == -1)
    {
        printf("error opening\n");
        perror(device);
        close(fd);
        return;
    }
    printf("opened /dev/ttyUSB0\n");

    writeResetToDefaults(fd);

    //sleep(1);
    
    // // query the device FW version
    // unsigned char command1[] = "$PMTK604*6D\r\n";
    // if (write(fd, command1, sizeof(command1)) == -1)
    // {
    //     printf("error writing\n");
    //     perror("perror writing");
    //     goto done;
    // }

    int count = 0;
    while (1) {
        count++;

        unsigned char response[1024];
        size_t bytes_read = read(fd, response, 1024);

        if(bytes_read == -1)
        {
            printf("error reading (error %d)\n", errno);
            perror("perror reading");
            break;
        }

        response[bytes_read] = '\0';

        printf("%s\n", response);

        //writeACK(fd);

        if (count == 1) {
            writeResetToDefaults(fd);
        }

        if (count == 10) {
            //writeVersionQuery(fd);
        }
    }

    done: 
        close(fd);
}