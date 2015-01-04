#include <stdio.h>  
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include "maestro.h"

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

void servo_controller_set_position(servo_controller *controller, uint8_t channel, float value) {
    float scaled = (value * 4000) + 4000;
    int target = (int)roundf(scaled);
    printf("[servo_controller] Setting ch%d to %f (%d us)\n", channel, value, target/4);

    unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
    if (write(controller->fd, command, sizeof(command)) == -1)
    {
      perror("[servo_controller] error writing");
      //return -1;
    }
    //return 0;
}



// Gets the position of a Maestro channel.
// See the "Serial Servo Commands" section of the user's guide.
int maestroGetPosition(int fd, unsigned char channel)
{
  unsigned char command[] = {0x90, channel};
  if(write(fd, command, sizeof(command)) == -1)
  {
    perror("error writing");
    return -1;
  }
   
  unsigned char response[2];
  if(read(fd,response,2) != 2)
  {
    perror("error reading");
    return -1;
  }
   
  return response[0] + 256*response[1];
}
 
// Sets the target of a Maestro channel.
// See the "Serial Servo Commands" section of the user's guide.
// The units of 'target' are quarter-microseconds.
int maestroSetTarget(int fd, unsigned char channel, unsigned short target)
{
  unsigned char command[] = {0x84, channel, target & 0x7F, target >> 7 & 0x7F};
  if (write(fd, command, sizeof(command)) == -1)
  {
    perror("error writing");
    return -1;
  }
  return 0;
}

void setServoPosition(int fd, unsigned char channel, float position) 
{
    float scaled = (position * 4000) + 4000;
    int target = (int)roundf(scaled);
    printf("Setting ch%d to %f (%d us)\n", channel, position, target/4);
    maestroSetTarget(fd, 0, target);
}

float randomFloat() {
    float r = (float)rand();
    float normalized = r / (float)RAND_MAX;
    return normalized;
}

void talkToServos()
{
  printf("Let's talk to servos!\n");

  // Open the Maestro's virtual COM port.
  const char * device = "/dev/ttyACM0";  // Linux
  int fd = open(device, O_RDWR | O_NOCTTY);
  if (fd == -1)
  {
    perror(device);
    return;// 1;
  }

  srand(time(0));

  int i = 0;
  while (i < 4) {
    sleep(1);
    float position = randomFloat();
    setServoPosition(fd, 0, position);
    i++;
  }
   
  close(fd);
  //return 0;
}