/* <mmu.h> */
/* Simple ligthwigth mmu that gives pointers to memory. It doesn't free 
 * at all. Only for testing porpouses
 */

#ifndef _MMU_H_
#define _MMU_H_

void *malloc(int size);

void free(void *ptr);
#endif


/* </mmu.h> */

