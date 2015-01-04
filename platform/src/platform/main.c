#include "platform.h"
#include "../chr-um6/regs/gp9_regs.h"
#include <stdio.h>

#define WARN_IF_FALSE(A) do { if (!(A)) { printf("warning: " #A "\n"); }} while (0);

void checkHealth(platform *platform) {
    uint32_t health = platform_get_input_value_int(platform, GP9_DREG_HEALTH);

    WARN_IF_FALSE(GP9_DREG_HEALTH_GET_GPS(health));
}

int main() {
  const char *sensor_device = "/dev/ttyUSB0";
  const char *servo_device = "/dev/ttyACM0";

  servo_controller *servo_controller = servo_controller_alloc(servo_device);
  chr_sensor *chr_sensor = chr_sensor_alloc(sensor_device);

  platform *platform = platform_alloc(chr_sensor, servo_controller);

  uint32_t settings = 0;

  GP9_CREG_COM_RATES7_SET_HEALTH_RATE(settings, 4);
  chr_sensor_write(chr_sensor, GP9_CREG_COM_RATES7, settings);

  float state = 0;

  while (1) {
    platform_set_output_value(platform, 0, state);
    platform_write_output_values(platform);
    platform_read_input_values(platform);

    checkHealth(platform);

    float z_accell = platform_get_input_value_float(platform, GP9_DREG_ACCEL_PROC_Z);
    z_accell /= 10; //roughly normalize gravity.
    state = z_accell;

    if (state < 0) {
        printf("sensor turned upside down. exiting.\n");
        break;
    }
  }

  platform_dealloc(platform);
  return 0;
}
