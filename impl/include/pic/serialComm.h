/* <serialComm.h> */

#ifndef _SERIALCOMM_H_
#define _SERIALCOMM_H_

#include "pic/package.h"
#include "pic/stateMachine.h"
#include "pic/packageBuffer.h"

#include "drivers/serial.h"


void serialComm_init();

void serialComm_charArrived(unsigned char c);

void serialComm_send(package_t *package);

int serialComm_packageAvailable();

package_t serialComm_dequeue();


static stateMachine_t machine;

void serialComm_init() {
	machine = stateMachine_new();
	packageBuffer_init();
}

void serialComm_charArrived(unsigned char c){
	state_t state;
	package_t package;
	
	state = stateMachine_state(&machine, c);
	switch(state){
		case state_command: case state_checksum: case state_data: {
			break;
		case state_finished:
			LOG("package finished");
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
			ERROR("serialComm::charArrived() package failed!");
		}
	}
}

void serialComm_send(package_t *package){
	unsigned char checksum;
	int i;
	
	checksum = package->command;
	serial_putc(COM1, package->command);
		
	for(i = 0; i < DATA_LENGTH ; i++){
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

#endif
/* </serialComm.h> */
