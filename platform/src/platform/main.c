#include <fcntl.h>
#include <endian.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "maestro.h"
#include "gps.h"
#include "platform.h"
#include "chr_sensor.h"
#include "../chr-um6/interface/chr_um6.h"
#include "../chr-um6/regs/um6_regs.h"
#include "../chr-um6/regs/gp9_regs.h"
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
         char result[5];
         memcpy(result, &out->fw_version.data, 4);
         result[4] = '\0';
         printf("the firmware version was %s", result);
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

void handle_data_gp9(um6_data_t *out, uint8_t ca, uint8_t *data)
{
   uint32_t data32_1 = be32toh(*(uint32_t *)data);
   uint32_t data32_2 = be32toh(*(uint32_t *)(data + UM6_DATA_ITEM_SIZE));
   switch (ca)
   {
      case GP9_DREG_VELOCITY_UP:
        printf("GP9_DREG_VELOCITY_UP\n");
        break;

      case GP9_DREG_QUAT_AB:
        printf("GP9_DREG_QUAT_AB\n");
        break;

      case GP9_DREG_VELOCITY_N:
        printf("GP9_DREG_VELOCITY_N\n");
        break;

      case GP9_DREG_GYRO_PROC_X:
        printf("GP9_DREG_GYRO_PROC_X\n");
        break;

      case GP9_DREG_MAG_PROC_X:
        printf("GP9_DREG_MAG_PROC_X\n");
        break;

      case GP9_DREG_GPS_LATITUDE:
        printf("GP9_DREG_GPS_LATITUDE\n");
        break;

      case GP9_DREG_GPS_LONGITUDE:
        printf("GP9_DREG_GPS_LONGITUDE\n");
        break;

      case GP9_DREG_POSITION_N:
        printf("GP9_DREG_POSITION_N\n");
        break;

      case GP9_DREG_EULER_PHI_THETA:
        printf("GP9_DREG_EULER_PHI_THETA\n");
        break;

      case GP9_DREG_GYRO_RAW1:
        printf("GP9_DREG_GYRO_RAW1\n");
        break;

      case GP9_DREG_HEALTH:
        printf("DREG_HEALTH\n");
        break;

      case GP9_DREG_GYRO_BIAS_Y:
        printf("GP9_DREG_GYRO_BIAS_Y\n");
        break;

      case GP9_DREG_BIAS_Y_VARIANCE:
        printf("GP9_DREG_BIAS_Y_VARIANCE\n");
        break;




      // case GP9_DREG_GYRO_BIAS_X:
      //   printf("GP9_DREG_GYRO_BIAS_X\n");
      //   break;

      // case GP9_DREG_GYRO_PROC_X:
      //   printf("GP9_DREG_GYRO_PROC_X\n");
      //   break;

      // case GP9_DREG_MAG_PROC_X:
      //   printf("GP9_DREG_MAG_PROC_X\n");
      //   break;


     default:
         printf("unhandled command: %X\n", ca);
   }
}

void writeComSettings(serialport_t *port) {

  um6_composer_t composer;
  um6_composer_init(&composer);

  uint32_t data = 0;
  //UM6_COMM_SET_VEL(data);
  //UM6_COMM_SET_REL(data);
  //UM6_COMM_SET_POS(data);
  //UM6_COMM_CLEAR_EU(data);
  UM6_COMM_SET_QT(data);
  //UM6_COMM_SET_MP(data);
  //UM6_COMM_SET_AP(data);
  //UM6_COMM_SET_GP(data);
  UM6_COMM_SET_MR(data);
  UM6_COMM_SET_AR(data);
  UM6_COMM_SET_GR(data);


  printf("about to compose.\n");
  int is_batch = 0;

  uint32_t u_val = htobe32(data);
  um6_composer_run(&composer, (uint8_t *)&u_val, UM6_DATA_ITEM_SIZE, is_batch, UM6_COMM);

  printf("sleeping 1\n");
  sleep(1);

  printf("about to write.\n");
  uint8_t *to_write = composer.data;
  int written = serial_write(port, (char *)to_write, composer.size);

  assert(written == composer.size);

}

void talkToIMU() {
  serialport_t port;
  serial_open(&port, "/dev/ttyUSB0", 115200, 0, 0, 0);

  printf("Opened the port.\n");

  //writeComSettings(&port);

  printf("sleeping 1\n");
  sleep(1);

  int count = 0;

  while (++count < 10) {

    printf("reading\n");

    sleep(1);
    size_t howBig = 2048;
    char rx_data[howBig];

    int message_length = serial_read_buffer(rx_data, howBig, &port);
    printf("read %d bytes\n", message_length);

    um6_parser_t parser;
    um6_parser_init(&parser);

    um6_data_t um6_data;
    int i = 0;
    for (; i < message_length; i++) {
      int result = um6_parser_run(&parser, rx_data[i]);

      switch (result) {
        case 0:
          break;
        case 1:
          handle_data_gp9(&um6_data, parser.ca, parser.data);
          break;
        case -1:
          um6_parser_init(&parser);
          printf("parse error\n");
          break;
        case -2:
          um6_parser_init(&parser);
          printf("bad checksum\n");
          break;
      }
    }
  }

  serial_close(&port);
}

int main() {
  const char *sensor_device = "/dev/ttyUSB0";
  const char *servo_device = "/dev/ttyACM0";

  platform *platform = platform_alloc(sensor_device, servo_device);

  float state = 0;

  while (1) {
    platform_set_output_value(platform, 0, state);
    platform_write_output_values(platform);
    platform_read_input_values(platform);
    float z_accell = platform_get_input_value_float(platform, GP9_DREG_ACCEL_PROC_Z);
    z_accell /= 10; //roughly normalize gravity.
    state = z_accell;
  }

  platform_dealloc(platform);

  return 0;

}
