/* <packageBuffer.c> */
#include "pic/packageBuffer.h"
#include "pic/package.h"

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
	buffer[head++]=package;
	return 1;
}

package_t packageBuffer_dequeu(){
	package_t ret;
	if(packageBuffer_isEmpty()){
		return package_null();
	}
	ret = buffer[tail++];
	return ret;
}

int packageBuffer_isEmpty(){
	return head == tail;
}

int packageBuffer_isFull(){
	return (head+1)%PACKAGEBUFFER_SIZE == tail%PACKAGEBUFFER_SIZE;
}

/* </packageBuffer.c> */
