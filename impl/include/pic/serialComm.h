/* <serialComm.h> */

#include "pic/package.h"

#ifndef _SERIALCOMM_H_
#define _SERIALCOMM_H_

#include "pic/package.h"

void serialComm_init();

void serialComm_charArrived(unsigned char c);

void serialComm_send(package_t *package);

int serialComm_packageAvailable();

package_t serialComm_dequeue();

#endif
/* </serialComm.h> */
