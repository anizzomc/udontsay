/* <packageBuffer.h> */

#ifndef _PACKAGEBUFFER_H_
#define _PACKAGEBUFFER_H_

#define PACKAGEBUFFER_SIZE 10

#include "pic/package.h"

void packageBuffer_init();

int packageBuffer_enqueue(package_t package);

package_t packageBuffer_dequeu();

int packageBuffer_isEmpty();

int packageBuffer_isFull();


static package_t buffer[PACKAGEBUFFER_SIZE];
static unsigned int head;
static unsigned int tail;

void packageBuffer_init(){
	int i;
	for (i = 0 ; i < PACKAGEBUFFER_SIZE ; i++){
		buffer[i] = package_null();
	}
	head = tail = 0;
}

int packageBuffer_enqueue(package_t package){
	if(packageBuffer_isFull()){
		return 0;
	}
	buffer[head++%PACKAGEBUFFER_SIZE]=package;
	return 1;
}

package_t packageBuffer_dequeu(){
	package_t ret;
	if(packageBuffer_isEmpty()){
		return package_null();
	}
	ret = buffer[tail++%PACKAGEBUFFER_SIZE];
	return ret;
}

int packageBuffer_isEmpty(){
	return head == tail;
}

int packageBuffer_isFull(){
	return (head+1)%PACKAGEBUFFER_SIZE == tail%PACKAGEBUFFER_SIZE;
}

#endif

/* </packageBuffer.h> */
