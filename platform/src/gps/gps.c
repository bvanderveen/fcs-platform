#include "gps.h"
#include <stdio.h>  
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


void talkToGPS() {
    printf("Let's talk to GPS!\n");

    const char * device = "/dev/ttyUSB0";  // Linux
    int fd = open(device, O_RDWR | O_NOCTTY);
    if (fd == -1)
    {
        printf("error opening\n");
        perror(device);
        goto done;
    }

    //sleep(1);

    // reset to defauls
    unsigned char command[] = "$PMTK314,-1*04\r\n";
    if (write(fd, command, sizeof(command)) == -1)
    {
        printf("error writing\n");
        perror("perror writing");
        goto done;
    }
    
    // // query the device FW version
    // unsigned char command1[] = "$PMTK604*6D\r\n";
    // if (write(fd, command1, sizeof(command1)) == -1)
    // {
    //     printf("error writing\n");
    //     perror("perror writing");
    //     goto done;
    // }

    while (1) {

        unsigned char response[1024];
        size_t bytes_read = read(fd, response, 1024);

        if(bytes_read == -1)
        {
            printf("error reading (error %d)\n", errno);
            perror("perror reading");
            goto done;
        }

        response[bytes_read] = '\0';

        printf("%s", response);
    }

    done: 
        close(fd);
}