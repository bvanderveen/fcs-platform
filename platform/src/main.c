#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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

int main()
{
  printf("Let's talk to servos!\n");

  // Open the Maestro's virtual COM port.
  const char * device = "/dev/ttyACM0";  // Linux
  int fd = open(device, O_RDWR | O_NOCTTY);
  if (fd == -1)
  {
    printf("Oh balls.\n");
    perror(device);
    return 1;
  }

  printf("yea balls.\n");
   
  //int position = maestroGetPosition(fd, 0);
  //printf("Current position is %d.\n", position); 
  srand(time(0));

  int i = 0;
  while (i < 4) {
    sleep(1);
    float r = (float)rand();
    float normalized = r / (float)RAND_MAX;
    printf("rand was %f\n", r);
    float scaled = (normalized * 4000) + 4000;

    int target = (int)roundf(scaled);

    printf("Setting target to %d (%d us).\n", target, target/4);
    maestroSetTarget(fd, 0, target);
    i++;
  }
   
  close(fd);
  return 0;
}