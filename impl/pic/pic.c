/* <pic.c> */

#include "pic/pic.h"
#include "types.h"
#include "stdlib.h"
#include "sys/mmu.h"

#include "drivers/serial.h"

#include "pic/serialMotors.h"
#include "pic/stateMachine.h"

#include "debug.h"

static void init();

static stateMachine_t machine;

void int_rda(){
	LOG("pic::int_rda() in");
	int c;
	state_t state;
	package_t package;
	if(serial_received(COM1)){
		c = serial_getc(COM1);
	} else {
		LOG("pic::int_rda() out");
		return;
	}
	
	
	switch((state = stateMachine_state(&machine, c))){
		case state_command: case state_size: case state_checksum: case state_data: {
			LOG("pic::int_rda() State: %s", stateToStr(state));
			break;
		case state_finished:
			LOG("pic::int_rda() package finished ok");
			package = stateMachine_package(&machine);
			stateMachine_reset(&machine);
			break;
		case state_failed:
			stateMachine_reset(&machine);
			LOG("pic::int_rda() package failed");
		}

	}
	LOG("pic::int_rda() out");
}

void proc_cicle() {
	
	init();
	
	while(1) {
		//desenconolar
		//procesar
		//enviar respuesta.
		
		yield(); //--> no darle bola
	}




}

void init() {
	LOG("pic::init() in");
	
	machine = stateMachine_new();
	stateMachine_reset(&machine);
	
	
	LOG("pic::init() out");
}

/* </pic.c> */
