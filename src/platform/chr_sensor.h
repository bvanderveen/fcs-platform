#include <stdint.h>

#include "sys/posix_serial.h"
#include "wire_format/um6_parser.h"
#include "wire_format/um6_composer.h"

#ifndef __CHR_SENSOR_H__
#define __CHR_SENSOR_H__

struct chr_sensor {
    serialport_t *port;
    um6_parser_t *parser;
    um6_composer_t *composer;
};
typedef struct chr_sensor chr_sensor;

typedef void(*chr_sensor_data_handler)(uint8_t channel, uint32_t *data, void *);

chr_sensor *chr_sensor_alloc(const char *device);
void chr_sensor_dealloc(chr_sensor *chr_sensor);

void chr_sensor_read(chr_sensor *chr_sensor, chr_sensor_data_handler handler, void *context);

// data length is the number of 32bit integers
int chr_sensor_write(chr_sensor *chr_sensor, uint8_t channel, uint32_t *data, uint8_t data_length);

#endif