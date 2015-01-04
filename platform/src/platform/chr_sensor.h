#include <stdint.h>

#include "../chr-um6/sys/posix_serial.h"
#include "../chr-um6/wire_format/um6_parser.h"

#ifndef __CHR_SENSOR_H__
#define __CHR_SENSOR_H__

struct chr_sensor {
    serialport_t *port;
    um6_parser_t *parser;
};
typedef struct chr_sensor chr_sensor;

typedef void(*chr_sensor_data_handler)(uint8_t channel, uint32_t data, void *);

chr_sensor *chr_sensor_alloc(const char *device);
void chr_sensor_dealloc(chr_sensor *chr_sensor);

void chr_sensor_update(chr_sensor *chr_sensor, chr_sensor_data_handler handler, void *context);

#endif