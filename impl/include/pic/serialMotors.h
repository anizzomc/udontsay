/* <serialMotors.h> */
#ifndef _SERIAL_MOTORS_H_
#define _SERIAL_MOTORS_H_

typedef struct {
	char command;
	char size;
	char *data;
	char checksum;
} package_t;

char *dataToStr(char *data, char size);

#endif
/* </serialMotors.h> */