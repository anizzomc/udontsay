/* <kbuffers.h> */

#ifndef _KBUFFERS_H_
#define _KBUFFERS_H_

/* This interface implements a circular buffer of any size without
 * dinamic memory. The objetive is to be used in many parts of the
 * system where a circular buffer is needed.
 */

typedef struct {
		void *buffer;
		int buffer_size;
		int data_size;
		int tail;
		int head;
} circular_buffer_t;

circular_buffer_t circular_buffer_init(void *buffer, int data_size, int buffer_size);

int circular_buffer_put(circular_buffer_t buffer, void *data);

int circular_buffer_get(circular_buffer_t buffer, void *data);

int circular_buffer_isFull(circular_buffer_t buffer);

int circular_buffer_isEmpty(circular_buffer_t buffer);

#endif

/* </kbuffers.h> */
