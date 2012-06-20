/* <serialMotors.h> */
#ifndef _SERIAL_MOTORS_H_
#define _SERIAL_MOTORS_H_

typedef enum {command_null = 0, command_ping} command_t;

typedef struct {
	unsigned char command;
	unsigned char size;
	unsigned char *data;
	unsigned char checksum;
} package_t;

int serialMotors_check(package_t package);

package_t serialMotors_process(package_t request);

#endif
/* </serialMotors.h> */
