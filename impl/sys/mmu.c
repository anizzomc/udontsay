/* <mmu.c> */

static char *membase = (void *) 0x400000; //The forth MB.


void *malloc(int size) {
	void *ret = (void *) membase;
	membase += size;
	return ret;
}

void free(void *ptr){
	//Nothing
}

/* </mmu.c> */
