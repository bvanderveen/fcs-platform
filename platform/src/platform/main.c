#include <fcntl.h>
#include <endian.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "maestro.h"
#include "../chr-um6/wire_format/um6_parser.h"
#include "../chr-um6/interface/chr_um6.h"
#include "../chr-um6/regs/um6_regs.h"
#include "../chr-um6/regs/um6_convert.h"

void handle_data(um6_data_t *out, uint8_t ca, uint8_t *data)
{
   uint32_t data32_1 = be32toh(*(uint32_t *)data);
   uint32_t data32_2 = be32toh(*(uint32_t *)(data + UM6_DATA_ITEM_SIZE));
   switch (ca)
   {
      case UM6_STATUS:
         printf("UM6_STATUS\n");
         out->status.data = data32_1;
         out->status.valid = 1;
         break;

      case UM6_EKF_MAG_VAR:
         printf("UM6_EKF_MAG_VAR\n");
         out->ekf_mag_var.data = int32_to_float(*(uint32_t *)data);
         out->ekf_mag_var.valid = 1;
         break;

      case UM6_EKF_ACC_VAR:
         printf("UM6_EKF_ACC_VAR\n");
         out->ekf_acc_var.data = int32_to_float(*(uint32_t *)data);
         out->ekf_acc_var.valid = 1;
         break;

      case UM6_EKF_PROC_VAR:
         printf("UM6_EKF_PROC_VAR\n");
         out->ekf_proc_var.data = int32_to_float(*(uint32_t *)data);
         out->ekf_proc_var.valid = 1;
         break;

      case UM6_TEMPERATURE:
         printf("UM6_TEMPERATURE\n");
         out->temperature.data = int32_to_float(*(uint32_t *)data);
         out->temperature.valid = 1;
         break;
      
      case UM6_COMM:
         printf("UM6_COMM\n");
         out->comm.data =  be32toh(*(uint32_t *)data);
         out->comm.valid = 1;
         break;
      
      case UM6_GYRO_BIAS1:
         printf("UM6_GYRO_BIAS1\n");
         out->gyro_bias.x = biguint16_to_int16(UM6_GYRO_BIAS1_GET_X(data32_1));
         out->gyro_bias.y = biguint16_to_int16(UM6_GYRO_BIAS1_GET_Y(data32_1));
         out->gyro_bias.z = biguint16_to_int16(UM6_GYRO_BIAS2_GET_Z(data32_2));
         out->gyro_bias.valid = 1;
         break;

      case UM6_GET_FW_VERSION:
         printf("UM6_GET_FW_VERSION\n");
         out->fw_version.data = data32_1;
         out->fw_version.valid = 1;
         break;
      
      case UM6_GYRO_RAW1:
         printf("UM6_GYRO_RAW1\n");
         out->gyro_raw.x = uint16_to_gyro(UM6_GYRO_RAW1_GET_X(data32_1));
         out->gyro_raw.y = uint16_to_gyro(UM6_GYRO_RAW1_GET_Y(data32_1));
         out->gyro_raw.z = uint16_to_gyro(UM6_GYRO_RAW2_GET_Z(data32_2));
         out->gyro_raw.valid = 1;
         break;

      case UM6_GYRO_PROC1:
         printf("UM6_GYRO_PROC1\n");
         out->gyro_proc.x = uint16_to_gyro(UM6_GYRO_PROC1_GET_X(data32_1));
         out->gyro_proc.y = uint16_to_gyro(UM6_GYRO_PROC1_GET_Y(data32_1));
         out->gyro_proc.z = uint16_to_gyro(UM6_GYRO_PROC2_GET_Z(data32_2));
         out->gyro_proc.valid = 1;
         break;
      
      case UM6_ACC_RAW1:
         printf("UM6_ACC_RAW1\n");
         out->acc_raw.x = uint16_to_acc(UM6_ACC_RAW1_GET_X(data32_1));
         out->acc_raw.y = uint16_to_acc(UM6_ACC_RAW1_GET_Y(data32_1));
         out->acc_raw.z = uint16_to_acc(UM6_ACC_RAW2_GET_Z(data32_2));
         out->acc_raw.valid = 1;
         break;

      case UM6_ACC_PROC1:
         printf("UM6_ACC_PROC1\n");
         out->acc_proc.x = uint16_to_acc(UM6_ACC_PROC1_GET_X(data32_1));
         out->acc_proc.y = uint16_to_acc(UM6_ACC_PROC1_GET_Y(data32_1));
         out->acc_proc.z = uint16_to_acc(UM6_ACC_PROC2_GET_Z(data32_2));
         out->acc_proc.valid = 1;
         break;
      
      case UM6_MAG_RAW1:
         printf("UM6_MAG_RAW1\n");
         out->mag_raw.x = uint16_to_mag(UM6_MAG_RAW1_GET_X(data32_1));
         out->mag_raw.y = uint16_to_mag(UM6_MAG_RAW1_GET_Y(data32_1));
         out->mag_raw.z = uint16_to_mag(UM6_MAG_RAW2_GET_Z(data32_2));
         out->mag_raw.valid = 1;
         break;

      case UM6_MAG_PROC1:
         printf("UM6_MAG_PROC1\n");
         out->mag_proc.x = uint16_to_mag(UM6_MAG_PROC1_GET_X(data32_1));
         out->mag_proc.y = uint16_to_mag(UM6_MAG_PROC1_GET_Y(data32_1));
         out->mag_proc.z = uint16_to_mag(UM6_MAG_PROC2_GET_Z(data32_2));
         out->mag_proc.valid = 1;
         break;

      case UM6_EULER1:
         printf("UM6_EULER1\n");
         out->euler.phi = uint16_to_euler(UM6_EULER1_GET_PHI(data32_1));
         out->euler.theta = uint16_to_euler(UM6_EULER1_GET_THETA(data32_1));
         out->euler.psi = uint16_to_euler(UM6_EULER2_GET_PSI(data32_2));
         out->euler.valid = 1;
         break;

      case UM6_ZERO_GYROS:
         break;

      case UM6_RESET_EKF:
         break;

      case UM6_SET_ACC_REF:
         break;

     case UM6_SET_MAG_REF:
         break;

     case UM6_RESET_TO_FACTORY:
         break;

     case UM6_BAD_CHECKSUM:
         //printf("bad checksum\n");
         break;

     default:
         printf("unhandled command: %X\n", ca);
   }
}


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

  int count = 0;

  while (++count < 10) {

    size_t howBig = 1024 * 2;
    unsigned char rx_data[howBig];

    int message_length = read(fd, &rx_data, howBig);

    printf("read %d bytes\n", message_length);

    um6_parser_t parser;
    um6_parser_init(&parser);

    um6_data_t um6_data;
    int i = 0;
    for (; i < message_length; i++) {
      int result = um6_parser_run(&parser, rx_data[i]);

      switch (result) {
        case 0:
          //printf("parsed byte");
          break;
        case 1:
          handle_data(&um6_data, parser.ca, parser.data);
          break;
        case -1:
          printf("parse error\n");
        case -2:
          printf("bad checksum\n");
      }
    }


    sleep(1);
  }

  close(fd);
  return 0;

}
