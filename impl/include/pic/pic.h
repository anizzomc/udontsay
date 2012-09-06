/* <pic.h> */
/* This files contains the "main" code of what is going to be in the
 * pic. The idea of this is to make it easy to reach for the code
 * and only do a simple CPA (Copy-Paste-Adaptate) */

#ifndef _PIC_H_
#define _PIC_H_

#define DEBUG_LOG
#include "debug.h"

void init();

/* The function that will be called when a serial interrupt raises
 * 
 */
void int_rda();


/* The main cicle of the program */
void proc_cicle();

#undef DEBUG_LOG
#endif
/* </pic.h> */
