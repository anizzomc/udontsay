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

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access, byte cero);

void kputchar(char c);

#endif /* KLIB_H_ */
