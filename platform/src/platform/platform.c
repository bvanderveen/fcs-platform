#include "platform.h"
#include <stdlib.h>
#include "../chr-um6/regs/um6_convert.h"

platform *platform_alloc(chr_sensor *chr_sensor, servo_controller *servo_controller) {
    platform *result = calloc(1, sizeof(platform));
    result->servo_controller = servo_controller;
    result->chr_sensor = chr_sensor;
    result->input_values_count = 0xff;
    result->input_values = calloc(result->input_values_count, sizeof(uint32_t));
    result->output_values_count = 6;
    result->output_values = calloc(result->output_values_count, sizeof(float));
    return result;
}

void platform_dealloc(platform *platform) {
    free(platform);
}

void platform_set_output_value(platform *platform, uint8_t channel, float value) {
    platform->output_values[channel] = value;
}

uint32_t platform_get_input_value_int(platform *platform, uint8_t channel) {
    return platform->input_values[channel];
}

float platform_get_input_value_float(platform *platform, uint8_t channel) {
    uint32_t int_value = platform_get_input_value_int(platform, channel);
    return int32_to_float(int_value);
}

void platform_chr_sensor_data_handler(uint8_t channel, uint32_t data, void *context) {
    platform *p = (platform *)context;
    p->input_values[channel] = data;
}

void platform_read_input_values(platform *platform) {
    chr_sensor_read(platform->chr_sensor, platform_chr_sensor_data_handler, platform);
}

void platform_write_output_values(platform *platform) {
    int i = 0;

    for (; i < platform->output_values_count; i++) {
        servo_controller_set_position(platform->servo_controller, i, platform->output_values[i]);
    }
}