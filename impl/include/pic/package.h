/* <package.h> */

#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include "string.h"

typedef enum {command_null, command_ping, command_pong} command_t;

typedef struct {
	command_t command;
	unsigned char size;
	unsigned char *data;
} package_t;

package_t package_new(command_t command, const unsigned char* data, unsigned char size);

package_t package_null();

void package_free(package_t *package);


package_t package_new(command_t command, const unsigned char* data, unsigned char size){
	package_t ret;
	
	ret.command = command;
	ret.size = size;
	ret.data = malloc(size);
	memcpy(ret.data, data, size);
	
	return ret;
}

package_t package_null(){
	package_t ret = {0, 0,NULL};
	return ret;
}

void package_free(package_t *package){
	package->command = command_null;
	if(package->data != NULL)
		free(package->data);
	package->data = NULL;
}


#endif

/* </packag.h> */
