#include "arch/interrupts.h"
#include "defs.h"
#include "multiboot.h"
#include "arch/handlers.h"
#include "arch/cpuid.h"
#include "drivers/serial.h"

DESCR_INT idt[0xF];	// IDT de 16 entradas
IDTR idtr;			// IDTR

void keyboard_handler();
void serial_handler();
void tick_handler();

int kmain(multiboot_info_t* mbd, unsigned int magic)
{

	setup_IDT_entry (&idt[0x08], 0x08, (dword)&_irq00Handler, ACS_INT, 0);
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&_irq01Handler, ACS_INT, 0);
	//setup_IDT_entry (&idt[0x0A], 0x08, (dword)&_irq02Handler, ACS_INT, 0);
	//setup_IDT_entry (&idt[0x0B], 0x08, (dword)&_irq03Handler, ACS_INT, 0);
	setup_IDT_entry (&idt[0x0C], 0x08, (dword)&_irq04Handler, ACS_INT, 0);
	//setup_IDT_entry (&idt[0x0D], 0x08, (dword)&_irq05Handler, ACS_INT, 0);

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;	
	_lidt (&idtr);	


	//Configure Handlers
	handlers_configure(0, tick_handler);
	handlers_configure(1, keyboard_handler);
	handlers_configure(4, serial_handler);


	//Configure Serial COM1
	serial_init(COM1, serial_bps_38400, "8N1");
	
	


	//Enable TimerTick, Keyboard and Serial
	picMasterMask(0xEC); 
	picSlaveMask(0xFF);
         
	_sti();

	kvinit();
	kclearScreen();
	kprintf("Kernel Loaded!\n");
	kprintf("Lower memory: %d\t Higher memory: %d\n", mbd->mem_lower, mbd->mem_upper);
	
	
	while(1){			
		asm("hlt");
	}


}

//Remove key from keyboard buffer.
void keyboard_handler() {
		_in(0x60);
}

void tick_handler() {

}

void serial_handler() {
	int c;
	if((c = serial_getc(COM1)) != -1){
		c += 'A' - 'a';
		serial_putc(COM1, c);
	}
}
