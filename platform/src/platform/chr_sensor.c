#include "chr_sensor.h"
#include <stdlib.h>
#include <stdio.h>

chr_sensor *chr_sensor_alloc(const char *device) {
    chr_sensor *result = calloc(1, sizeof(chr_sensor));
    result->port = calloc(1, sizeof(serialport_t));
    serial_open(result->port, device, 115200, 0, 0, 0);
    result->parser = calloc(1, sizeof(um6_parser_t));
    um6_parser_init(result->parser);
    return result;
}

void chr_sensor_dealloc(chr_sensor *chr_sensor) {
    serial_close(chr_sensor->port);
    free(chr_sensor);
}

void chr_sensor_update(chr_sensor *chr_sensor, chr_sensor_data_handler handler, void *context) {
    size_t howBig = 2048;
    char rx_data[howBig];

    int message_length = serial_read_buffer(rx_data, howBig, chr_sensor->port);
    printf("read %d bytes\n", message_length);

    um6_parser_t *parser = chr_sensor->parser;

    int i = 0;
    for (; i < message_length; i++) {
        int result = um6_parser_run(parser, rx_data[i]);

        switch (result) {
            case 0:
                break;
            case 1:
                handler(parser->ca, (uint32_t)parser->data, context);
                break;
            case -1:
                um6_parser_init(parser);
                printf("parse error\n");
                break;
            case -2:
                um6_parser_init(parser);
                printf("bad checksum\n");
                break;
        }
    }
}