/* <serialMotors.h> */
#ifndef _SERIAL_MOTORS_H_
#define _SERIAL_MOTORS_H_

#define DEBUG_LOG
#include "debug.h"

#include "pic/package.h"

package_t serialMotors_process(package_t request);

static package_t do_ping(package_t request);

package_t serialMotors_process(package_t request){
	package_t response = package_null();

	
	switch(request.command){
		case command_null: {
			WARN("serialMotors::process() null package!");
		}
		break;
		case command_ping:{
			LOG("serialMotors::process() do_ping()");
			response = do_ping(request);
		}
		break;
		default: {
			WARN("serialMotors::process() default clause");
		}
		break;
	}

	return response;
}

static package_t do_ping(package_t request){
	return package_new(command_pong, request.data);
}

#undef DEBUG_LOG
#endif
/* </serialMotors.h> */
