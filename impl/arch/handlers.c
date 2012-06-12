
#include "arch/handlers.h"
#include "types.h"
#include "klib.h"
#include "stdlib.h"

#define  QTY_HANDLERS 16 //Amount of handlers by the system.

handlerfnc_t handlers[QTY_HANDLERS] = {0};

void handlers_configure(int irq, handlerfnc_t fnc) {
	handlers[irq] = fnc;
}

handlerfnc_t handlers_get(int irq){
	return handlers[irq];
}

void irqDispatcher(dword irq){

	if(handlers[irq] != NULL){
		handlers[irq]();
	}

	return;
}
