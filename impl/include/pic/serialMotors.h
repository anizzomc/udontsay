/* <serialMotors.h> */
#ifndef _SERIAL_MOTORS_H_
#define _SERIAL_MOTORS_H_

typedef struct {
	unsigned char command;
	unsigned char size;
	unsigned char *data;
	unsigned char checksum;
} package_t;



#endif
/* </serialMotors.h> */
