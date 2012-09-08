
#include "pic/pic.h"
#include "pic/serialComm.h"
#include "pic/serialMotors.h"

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

		}
		yield(); //--> no darle bola
	}
}


void init() {
	serialComm_init();
}
