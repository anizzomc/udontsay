/* <pic.c> */

#include "pic/pic.h"
#include "types.h"
#include "stdlib.h"
#include "sys/mmu.h"

#include "drivers/serial.h"

#include "pic/serialMotors.h"
#include "pic/serialComm.h"

#define DEBUG_LOG
#include "debug.h"


static void init();

void int_rda(){
	
	int c;
	if(serial_received(COM1))
		c = serial_getc(COM1);
	else
		return;
	serialComm_charArrived(c);
}

void proc_cicle() {
	package_t request, response;
	
	init();
	enable_interrupts();
	
	while(1) {

		if(serialComm_packageAvailable()){
			disable_interrupts();
			request = serialComm_dequeue();
			enable_interrupts();
			
			response = serialMotors_process(request);
			
			serialComm_send(&response);
			package_free(&response);
			package_free(&request);
		}
		yield(); //--> no darle bola
	}
}

static void init() {
	serialComm_init();
}
/* </pic.c> */
