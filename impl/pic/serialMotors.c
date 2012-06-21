/* <serialMotors.c> */

#include "klib.h"
#include "string.h"

#define DEBUG_LOG
#include "debug.h"

#include "pic/serialMotors.h"
#include "pic/package.h"

//TODO: Armar como Stub

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
	return package_new(command_pong, request.data, request.size);
}
/* </serialMotors.c> */
