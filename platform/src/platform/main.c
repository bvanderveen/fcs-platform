#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "maestro.h"
#include "../chr-um6/wire_format/um6_parser.h"

int main() {

  talkToServos();

  uint8_t accel_xy = 0x58;
  uint8_t accel_z = 0x59;


  // Open the Maestro's virtual COM port.
  const char * device = "/dev/ttyUSB0";  // Linux
  int fd = open(device, O_RDWR | O_NOCTTY);
  if (fd == -1)
  {
    perror(device);
    return 1;
  }

  printf("Opened the file");

  while (1) {

    size_t howBig = 1024 * 2;
    unsigned char rx_data[howBig];

    int message_length = read(fd, &rx_data, howBig);

    printf("read %d bytes\n", message_length);

    um6_parser_t parser;
    um6_parser_init(&parser);

    for (int i = 0; i < message_length; i++) {
      int result = um6_parser_run(&parser, rx_data[i]);

      switch (result) {
        case 0:
          //printf("parsed byte");
          break;
        case 1:
          printf("parsed packet!\n");
          break;
        case -1:
          printf("parse error\n");
        case -2:
          printf("bad checksum\n");
      }
    }
  }

  close(fd);
  return 0;

}
