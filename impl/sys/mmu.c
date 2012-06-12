/* <mmu.c> */

#include "types.h"
#include "stdlib.h"

#define MAX_MEMORY 10*1024*1024 //10 MB
#define MEM_BASE	0x400000
#define MEM_CEIL (MEM_BASE + MAX_MEMORY)


static char *membase = (void *) MEM_BASE; //The forth MB.


void *malloc(int size) {
	void *ret = (void *) membase;
	
	if((dword)(membase + size) > (dword)MEM_CEIL){
		return NULL;
	}
	
	membase += size;
	return ret;
}

void free(void *ptr){
	//Nothing
}

/* </mmu.c> */
