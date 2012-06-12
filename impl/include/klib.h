/*
 * klib.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef KLIB_H_
#define KLIB_H_

#include "types.h"

void kclearScreen();

void kvinit();

void _lidt(dword idt);

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access, byte cero);

void kputchar(char c);

void kprintf(const char *fmt, ...);

void enable_interrupts();

void yield();

void disable_interrupts();


#endif /* KLIB_H_ */
