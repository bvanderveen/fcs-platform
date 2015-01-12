#include <stdio.h>  
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "servo_controller.h"

servo_controller *servo_controller_alloc(const char *device) {
    servo_controller *controller = calloc(1, sizeof(servo_controller));

    controller->fd = open(device, O_RDWR | O_NOCTTY);

    if (controller->fd == -1)
    {
        perror(device);
        servo_controller_dealloc(controller);
        return NULL;
    }

    return controller;
}

void servo_controller_dealloc(servo_controller *controller) {
    if (controller->fd != -1) {
        free(controller);
    }
}

int servo_controller_set_position(servo_controller *controller, uint8_t channel, float value) {
    if (value < 0) {
        value = 0;
    }
    if (value > 1.0) {
        value = 1.0;
    }
    float scaled = (value * 4000) + 4000;
    int target = (int)roundf(scaled);
    //printf("[servo_controller] Setting ch%d to %f (%d us)\n", channel, value, target/4);

    unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
    if (write(controller->fd, command, sizeof(command)) == -1)
    {
        perror("[servo_controller] error writing");
        return -1;
    }
    return 0;
}