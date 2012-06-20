/* <pic.c> */

#include "pic/pic.h"
#include "types.h"
#include "stdlib.h"
#include "sys/mmu.h"

#include "drivers/serial.h"

#include "pic/serialMotors.h"
#include "pic/stateMachine.h"
#include "pic/packageBuffer.h"

#define DEBUG_LOG
#include "debug.h"



static void init();

static stateMachine_t machine;

static void sendResponse(package_t package);

void int_rda(){
	//LOG("pic::int_rda() in");
	int c;
	state_t state;
	package_t package;
	if(serial_received(COM1)){
		c = serial_getc(COM1);
	} else {
		//LOG("pic::int_rda() out");
		return;
	}
	
	
	switch((state = stateMachine_state(&machine, c))){
		case state_command: case state_size: case state_checksum: case state_data: {
		//	LOG("pic::int_rda() State: %s", stateToStr(state));
			break;
		case state_finished:
			LOG("pic::int_rda() package finished ok");
			package = stateMachine_package(&machine);
			stateMachine_reset(&machine);
			
			if (!packageBuffer_isFull()){
				LOG("pic::int_rda() enqueue package");
				packageBuffer_enqueue(package);
			} else {
				LOG("pic::int_rda() queue full <-- take action!");
			}
			break;
		case state_failed:
			stateMachine_reset(&machine);
			LOG("pic::int_rda() package failed <-- take action!");
		}

	}
	//LOG("pic::int_rda() out");
}

void proc_cicle() {
	
	init();
	
	while(1) {
		package_t request, response;
		int shouldProcess = 0;
		disable_interrupts();
		if(!packageBuffer_isEmpty()){
			LOG("pic::proc_cicle() package available dequeuing");
			shouldProcess = 1;
			request = packageBuffer_dequeu();
		}
		enable_interrupts();
		
		if(shouldProcess){
			LOG("pic::proc_cicle() processing package");
			response = serialMotors_process(request);
			sendResponse(response);
		}
		
		//send response
		yield(); //--> no darle bola
	}
}

static void init() {
	LOG("pic::init() in");
	
	machine = stateMachine_new();
	stateMachine_reset(&machine);
	
	packageBuffer_init();
	
	LOG("pic::init() out");
}

static void sendResponse(package_t package){
	LOG("pic::sendResponse() sending package");
	int i;
	serial_putc(COM1, package.command);
	serial_putc(COM1, package.size);
	for(i = 0; i < package.size ; i++){
		serial_putc(COM1, package.data[i]);
	}
	serial_putc(COM1, package.checksum);
}
/* </pic.c> */
