/* <package.h> */

#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include "string.h"
#include "types.h"

#define DATA_LENGTH 4

typedef enum {command_null, command_ping, command_pong} command_t;

typedef struct {
	command_t command;
	byte data[DATA_LENGTH];
//  byte checksum
} package_t;

package_t package_new(command_t command,byte data[]);

package_t package_null();

package_t package_new(command_t command, byte data[]){
	package_t ret;
	int i;
	
	ret.command = command;
	
	for(i = 0; i < DATA_LENGTH ; i++)
		ret.data[i] = data[i];
	
	return ret;
}

package_t package_null(){
	package_t ret;
	int i;
	
	ret.command = command_null;
	
	for(i = 0; i < DATA_LENGTH ; i++)
		ret.data[i] = 0;
	
	return ret;
}

#endif

/* </packag.h> */
