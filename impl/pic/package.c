/* <package.h> */

#include "sys/mmu.h"
#include "klib.h"
#include "stdlib.h"
#include "string.h"

#include "pic/package.h"

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


/* </package.h> */
