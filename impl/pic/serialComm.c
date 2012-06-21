/* <serialComm.h> */

#define DEBUG_ERROR
#include "debug.h"

#include "drivers/serial.h"

#include "pic/serialComm.h"
#include "pic/package.h"
#include "pic/packageBuffer.h"
#include "pic/stateMachine.h"

static stateMachine_t machine;

void serialComm_init() {
	machine = stateMachine_new();
	packageBuffer_init();
}

void serialComm_charArrived(unsigned char c){
	state_t state;
	package_t package;

	switch((state = stateMachine_state(&machine, c))){
		case state_command: case state_size: case state_checksum: case state_data: {
			break;
		case state_finished:
			package = stateMachine_package(&machine);
			stateMachine_reset(&machine);
			
			if (!packageBuffer_isFull()){
				packageBuffer_enqueue(package);
			} else {
				ERROR("serialComm::charArrived() queue full <-- take action!");
			}
			break;
		case state_failed:
			stateMachine_reset(&machine);
			ERROR("serialComm::charArrived() package failed <-- take action!");
		}
	}
}

void serialComm_send(package_t *package){
	unsigned char checksum;
	int i;
	
	checksum = package->command;
	serial_putc(COM1, package->command);
	checksum ^= package->size;
	serial_putc(COM1, package->size);
	
	for(i = 0; i < package->size ; i++){
		checksum ^= package->data[i];
		serial_putc(COM1, package->data[i]);
	}
	
	serial_putc(COM1, checksum);
}

int serialComm_packageAvailable(){
	return !packageBuffer_isEmpty();
}

package_t serialComm_dequeue(){
	if(!packageBuffer_isEmpty())
		return packageBuffer_dequeu();
	return package_null();
}

/* </serialComm.h> */
