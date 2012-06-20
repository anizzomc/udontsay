/* <serialMotors.c> */

#include "klib.h"
#include "string.h"

#define DEBUG_LOG
#include "debug.h"

#include "pic/serialMotors.h"



static package_t do_ping(package_t request);

static package_t nullPackage();

int serialMotors_check(package_t package){
	unsigned char checksum;
	int i;
	checksum = package.command;
	checksum ^= package.size;
	for(i = 0; i < package.size ; i++){
		checksum ^= package.data[i];
	}
	return checksum == package.checksum;
}

package_t serialMotors_process(package_t request){
	package_t response = nullPackage();

	
	switch(request.command){
		case command_null: {
			WARN("serialMotors::process() null package!");
			response = nullPackage();
		}
		break;
		case command_ping:{
			LOG("serialMotors::process() do_ping()");
			response = do_ping(request);
		}
		break;
		default: {
			WARN("serialMotors::process() default clause");
			response = nullPackage();
		}
		break;
	}

	return response;
}

static package_t nullPackage(){
	package_t ret = {0, 0, NULL, 0};
	return ret;
}

static package_t do_ping(package_t request){
	package_t ret;
	int i;
	
	ret.command = command_ping;
	ret.size = request.size;
	ret.data = malloc(request.size);
	
	for(i = 0; i < request.size ; i++){
		ret.data[i] = request.data[i];
	}
	ret.checksum = request.checksum;
	return ret;
}
/* </serialMotors.c> */
