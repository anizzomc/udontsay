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

#endif

/* </packageBuffer.h> */
