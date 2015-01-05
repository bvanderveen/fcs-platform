#include "platform.h"
#include "gp9_regs.h"
#include "../chr-um6/regs/um6_convert.h"
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#define HEALTH_REPORT(A) do { printf("[health] " #A " = %d\n", (A)); } while (0);

void checkHealth(platform *platform) {
    uint32_t health = platform_get_input_value_int(platform, GP9_DREG_HEALTH);

    HEALTH_REPORT(GP9_DREG_HEALTH_GET_GPS(health));
    HEALTH_REPORT(GP9_DREG_HEALTH_GET_MAG(health));
    HEALTH_REPORT(GP9_DREG_HEALTH_GET_GYRO(health));
    HEALTH_REPORT(GP9_DREG_HEALTH_GET_ACCEL(health));
    HEALTH_REPORT(GP9_DREG_HEALTH_GET_PRESS(health));
    HEALTH_REPORT(GP9_DREG_HEALTH_GET_GPS_ST(health));
    HEALTH_REPORT(GP9_DREG_HEALTH_GET_OVF(health));
}

void writeSettings(chr_sensor *chr_sensor) {
  uint32_t settings;

  settings = 0;
  assert(chr_sensor_write(chr_sensor, GP9_RESET_TO_FACTORY, &settings, 1) > -1);

  settings = 0;
  GP9_CREG_COM_RATES7_SET_HEALTH_RATE(settings, 2);
  assert(chr_sensor_write(chr_sensor, GP9_CREG_COM_RATES7, &settings, 1) > -1);

  settings = 0;
  GP9_CREG_COM_RATES4_SET_ALL_PROC_RATE(settings, 1);
  assert(chr_sensor_write(chr_sensor, GP9_CREG_COM_RATES4, &settings, 1) > -1);

  settings = 0;
  GP9_CREG_COM_RATES2_SET_ALL_RAW_RATE(settings, 0);
  assert(chr_sensor_write(chr_sensor, GP9_CREG_COM_RATES2, &settings, 1) > -1);
}

int main() {
  const char *sensor_device = "/dev/ttyUSB0";
  const char *servo_device = "/dev/ttyACM0";

  servo_controller *servo_controller = servo_controller_alloc(servo_device);
  chr_sensor *chr_sensor = chr_sensor_alloc(sensor_device);

  platform *platform = platform_alloc(chr_sensor, servo_controller);

  //writeSettings(chr_sensor);

  float state = 0;

  while (1) {
    usleep(20 * 1000);

    platform_set_output_value(platform, 0, -state);
    platform_write_output_values(platform);
    platform_read_input_values(platform);

    //checkHealth(platform);

    //uint32_t raw_z = platform_get_input_value_int(platform, GP9_DREG_ACC_RAW2);

    //int raw_z_accell_int = GP9_DREG_ACC_RAW2_GET_Z(raw_z);
    // printf("raw_z_accell_int = %d\n", raw_z_accell_int);
    // printf("biguint16_to_int16(raw_z_accell_int) = %d\n", biguint16_to_int16(raw_z_accell_int));

    float accel_proc_z = platform_get_input_value_float(platform, GP9_DREG_ACCEL_PROC_Z);

    // printf("accel_proc_z = %f\n", accel_proc_z);
    state = accel_proc_z / 9.81f;//roughly normalize gravity.

    if (state > 0) {
        printf("sensor turned upside down. exiting.\n");
        break;
    }
  }

  servo_controller_dealloc(servo_controller);
  chr_sensor_dealloc(chr_sensor);
  platform_dealloc(platform);
  return 0;
}
