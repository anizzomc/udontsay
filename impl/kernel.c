#include "arch/interrupts.h"
#include "defs.h"
#include "multiboot.h"
#include "arch/handlers.h"
#include "arch/cpuid.h"

DESCR_INT idt[0xA];	// IDT de 11 entradas
IDTR idtr;			// IDTR


/**********************************************
kmain() 
Punto de entrada de codigo C.
*************************************************/

int kmain(multiboot_info_t* mbd, unsigned int magic)
{

	setup_IDT_entry (&idt[0x08], 0x08, (dword)&_irq00Handler, ACS_INT, 0);
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_irq01Handler, ACS_INT, 0);
	//setup_IDT_entry (&idt[0x0A], 0x08, (dword)&_irq02Handler, ACS_INT, 0);
	//setup_IDT_entry (&idt[0x0B], 0x08, (dword)&_irq03Handler, ACS_INT, 0);
	//setup_IDT_entry (&idt[0x0C], 0x08, (dword)&_irq04Handler, ACS_INT, 0);
	//setup_IDT_entry (&idt[0x0D], 0x08, (dword)&_irq05Handler, ACS_INT, 0);


	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	


	//Todas las interrupciones desabilidas.
	picMasterMask(0xFC); 
	picSlaveMask(0xFF);
        
	_sti();

	kvinit();
	kclearScreen();
	kprintf("Kernel Loaded!\n");
	kprintf("Lower memory: %d\t Higher memory: %d\n", mbd->mem_lower, mbd->mem_upper);
	
	
	while(1){
	}


}
