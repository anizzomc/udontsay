/* <kbuffers.c> */

#include "kbuffers.h"
#include "string.h"

circular_buffer_t circular_buffer_init(void *buffer, int data_size, int buffer_size){
	circular_buffer_t ret;
	
	ret.buffer = buffer;
	ret.buffer_size = buffer_size;
	ret.data_size = data_size;
	ret.tail = ret.head = 0;
}

int circular_buffer_isFull(circular_buffer_t buffer) {
	return (buffer.head+1)%buffer.data_size == buffer.tail%buffer.data_size;
}

int circular_buffer_isEmpty(circular_buffer_t buffer){
	return buffer.tail == buffer.head;
}

int circular_buffer_put(circular_buffer_t buffer, void *data){
	if(circular_buffer_isFull(buffer)){
		return 0;
	}	
	memcpy((char *)buffer) + (buffer.head%buffer.buffer_size)*buffer.data_size), data, buffer.data_size);
	buffer.head++;
	return 1;
}

int circular_buffer_get(circular_buffer_t buffer, void *data){
	if(circular_buffer_isEmpty(buffer)){
		return 0;
	}
	memcpy(data, (char *)buffer) + (buffer.head%buffer.buffer_size)*buffer.data_size), buffer.data_size);
	buffer.tail--;
	return 1;
}

/* </kbuffers.c> */
