/* <stateMachine.h> */
#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "serialMotors.h"

#define NULL_COMMAND 0	//Nothing

typedef enum {state_command, state_size, state_data, state_checksum, state_finished, state_failed} state_t;

typedef struct {
	package_t package;
	state_t state;
	int datacount;
	char checksum;
} stateMachine_t;

char *stateToStr(state_t state);

stateMachine_t stateMachine_new();

void stateMachine_reset(stateMachine_t *machine);

state_t stateMachine_state(stateMachine_t *machine, char data);

package_t stateMachine_package(stateMachine_t *machine);

#endif
/* </stateMachine.h> */
