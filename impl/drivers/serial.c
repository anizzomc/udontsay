/* <serial.c> */

#include "drivers/serial.h"
#include "arch/io.h"


#define BUFFER_SIZE 256

//static int baseaddress[] = {COM1};

void serial_init(int serial_port, serial_bps_t serial_speed, char *config) {
   _out(serial_port + 1, 0x00);    // Disable all interrupts
   _out(serial_port + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   _out(serial_port + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   _out(serial_port + 1, 0x00);    //                  (hi byte)
   _out(serial_port + 3, 0x03);    // 8 bits, no parity, one stop bit
   _out(serial_port + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   _out(serial_port + 4, 0x0B);    // IRQs enabled, RTS/DSR set
   _out(serial_port + 1, 0x01);	//Enable Interrups
}

int serial_received(int port) {
   return _in(port + 5) & 1;
}

int serial_getc(int port) {
	if(!serial_received(port)) {
		return -1;
	}
		return _in(port);
}


void serial_putc(int port, int c){
	_out(port, c);
}


/* </serial.c> */
