/* <stateMachine.c> */

#include "stdlib.h"
#include "debug.h"
#include "string.h"

#include "pic/stateMachine.h"
#include "pic/package.h"

stateMachine_t stateMachine_new() {
	stateMachine_t ret;
	
	ret.package = package_null();
	ret.state = state_command;
	ret.datacount = 0;
	ret.checksum = 0;
	
	return ret;
}

void stateMachine_reset(stateMachine_t *machine) {
	package_free(&machine->package);
	machine->package = package_null();
	machine->datacount = 0;
	machine->checksum = 0;
	machine->state = state_command;
}

state_t stateMachine_state(stateMachine_t *machine, char data) {

	switch(machine->state){
		case state_command: {
			machine->package.command = data;
			machine->state = state_size;
		}
		break;
		case state_size: {
			machine->package.size = data;
			machine->package.data = (unsigned char *) malloc(data);
			machine->datacount = data;
			machine->state = state_data;
		}
		break;
		case state_data: {
			machine->package.data[machine->package.size - machine->datacount] = data;
			machine->datacount--;
			if(machine->datacount == 0){
				machine->state = state_checksum;
			}
		} 
		break;
		case state_checksum: {
			machine->state = state_finished;
		}
		break;
		case state_finished: case state_failed:
		{ 
			return machine->state; 
		}
		break;
	}
	
	if(machine->state != state_finished){
		machine->checksum ^= data;
	} else {
		if(machine->checksum != data){
			machine->state = state_failed;
			package_free(&machine->package);
		}
	}
	
	return machine->state;
}

package_t stateMachine_package(stateMachine_t *machine){
	return machine->package;
}

char *stateToStr(state_t state) {
	switch(state) {
		case state_command:
			return "state_command";
		case state_size:
			return "state_size";
		case state_data:
			return "state_data";
		case state_checksum:
			return "state_checksum";
		case state_finished:
			return "state_finished";
		case state_failed:
			return "state_failed";
	}
	return "error";

}


/* </stateMachine.c> */
