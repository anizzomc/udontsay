
#include "types.h"
#include "klib.h"


void irqDispatcher(dword irq){

	kprintf("Received IRQ:%x\n", irq);
	
	
	if(irq == 1) { //keyboard
		kprintf("Scancode: %x\n", _in(0x60));
	}
	
	return;
}

void int_08(){

}
