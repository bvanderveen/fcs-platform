
#ifndef __SERVO_CONTROLLER_H__
#define __SERVO_CONTROLLER_H__

struct servo_controller {
	int fd;
	uint8_t channel_count;
};
typedef struct servo_controller servo_controller;

servo_controller *servo_controller_alloc(const char *device);
void servo_controller_dealloc(servo_controller *controller);
int servo_controller_set_position(servo_controller *controller, uint8_t channel, float value);

#endif