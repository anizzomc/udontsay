/*
 * handlers.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "types.h"


//Declare how the handlers are used.
typedef void (*handlerfnc_t)(void);

//Function that receives the IRQ events by hardware.
void irqDispatcher(dword irq);

void handlers_configure(int irq, handlerfnc_t fnc);

handlerfnc_t handlers_get(int irq);

#endif /* HANDLERS_H_ */
