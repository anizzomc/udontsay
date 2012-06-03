/*
 * interrups.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef INTERRUPS_H_
#define INTERRUPS_H_

#include "types.h"

void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);

void _cli(void);

void _sti(void);

void picMasterMask(byte mask);

void picSlaveMask(byte mask);

void int_80_hand();

void lidt(IDTR *idtr);

//Termina la ejecución de la cpu.
void haltcpu(void);

#endif /* INTERRUPS_H_ */
