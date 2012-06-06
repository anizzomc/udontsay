/* <serial.h> */

#ifndef _DRIVERS_SERIAL_H_
#define _DRIVERS_SERIAL_H_

#define COM1 0x3F8

typedef enum {serial_bps_38400} serial_bps_t;

/* Mocked serial init */
void serial_init(int serial_port, serial_bps_t serial_speed, char *config);

/* Returns true if there are characters in the S.Port */
int serial_received(int port);

/* Will return -1 if there is no char */
int serial_getc(int port);

/* Send character to serial port */
void serial_putc(int port, int c);

#endif
