/*
 * handlers.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "types.h"

void irqDispatcher(dword irq);

void int_08_hand();

#endif /* HANDLERS_H_ */
