/* <stateMachine.h> */
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "pic/package.h"

#define DEBUG_LOG
#include "debug.h"

#define NULL_COMMAND 0	//Nothing

typedef enum {state_command, state_data, state_checksum, state_finished, state_failed} state_t;

typedef struct {
	package_t package;
	state_t state;
	int datacount;
	unsigned char checksum;
} stateMachine_t;

char *stateToStr(state_t state);

stateMachine_t stateMachine_new();

void stateMachine_reset(stateMachine_t *machine);

state_t stateMachine_state(stateMachine_t *machine,unsigned char data);

package_t stateMachine_package(stateMachine_t *machine);


stateMachine_t stateMachine_new() {
	stateMachine_t ret;
	
	ret.package = package_null();
	ret.state = state_command;
	ret.datacount = 0;
	ret.checksum = 0;
	
	return ret;
}

void stateMachine_reset(stateMachine_t *machine) {
	machine->package = package_null();
	machine->datacount = 0;
	machine->checksum = 0;
	machine->state = state_command;
}

state_t stateMachine_state(stateMachine_t *machine, unsigned char data) {
	LOG("Machine state: %s", stateToStr(machine->state));
	LOG("Data arrived: %x", data);

	switch(machine->state){
		case state_command: {
			machine->package.command = data;
			machine->state = state_data;
			machine->datacount = 0;
			LOG("switched to state_data");
		}
		break;
		case state_data: {
			machine->package.data[machine->datacount] = data;
			machine->datacount++;
			LOG("Datacount: %d", machine->datacount);
			if(machine->datacount == DATA_LENGTH){
				machine->state = state_checksum;
				LOG("switched to state_checksum");
			}
		} 
		break;
		case state_checksum: {
			machine->state = state_finished;
			LOG("switched to state_finished");
		}
		case state_failed: case state_finished:
		break;
	}
	
	if(machine->state != state_finished){
		machine->checksum ^= data;
		LOG("Current Checksum: %x",machine->checksum);
	} else {
		if(machine->checksum != data){
			LOG("checksum failed");
			machine->state = state_failed;
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

#undef DEBUG_LOG
#endif
/* </stateMachine.h> */
