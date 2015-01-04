#include "chr_sensor.h"
#include "maestro.h"

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

struct platform {
    chr_sensor *chr_sensor;
    servo_controller *servo_controller;
    uint8_t input_values_count;
    uint32_t *input_values;
    uint8_t output_values_count;
    float *output_values;
};
typedef struct platform platform;

platform *platform_alloc(const char *sensor_device, const char *servo_device);
void platform_dealloc(platform *platform);

void platform_set_output_value(platform *platform, uint8_t channel, float value);

uint32_t platform_get_input_value_int(platform *platform, uint8_t channel);
float platform_get_input_value_float(platform *platform, uint8_t channel);

void platform_write_output_values(platform *platform);
void platform_read_input_values(platform *platform);

#endif