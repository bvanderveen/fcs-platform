#include "platform.h"
#include <stdlib.h>

platform *platform_alloc(const char *sensor_device, const char *servo_device) {
    platform *result = calloc(1, sizeof(platform));
    result->servo_controller = servo_controller_alloc(servo_device);
    result->chr_sensor = chr_sensor_alloc(sensor_device);
    result->input_values_count = 0xff;
    result->input_values = calloc(result->input_values_count, sizeof(uint32_t));
    result->output_values_count = 6;
    result->output_values = calloc(result->output_values_count, sizeof(float));
    return result;
}

void platform_dealloc(platform *platform) {
    servo_controller_dealloc(platform->servo_controller);
    chr_sensor_dealloc(platform->chr_sensor);
    free(platform);
}

void platform_set_output_value(platform *platform, uint8_t channel, float value) {
    platform->output_values[channel] = value;
}

uint32_t platform_get_input_value_int(platform *platform, uint8_t channel) {
    return platform->input_values[channel];
}

float platform_get_input_value_float(platform *platform, uint8_t channel) {
    return 0.0;
}

void platform_chr_sensor_data_handler(uint8_t channel, uint32_t data, void *context) {
    platform *p = (platform *)context;
    p->input_values[channel] = data;
}

void platform_read_input_values(platform *platform) {
    chr_sensor_update(platform->chr_sensor, platform_chr_sensor_data_handler, platform);
}

void platform_write_output_values(platform *platform) {
    int i = 0;

    for (; i < platform->output_values_count; i++) {
        servo_controller_set_position(platform->servo_controller, i, platform->output_values[i]);
    }
}