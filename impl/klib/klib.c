/*
 * klib.c
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#include "types.h"
#include "klib.h"
#include "string.h"

void kprintf (const char *format, ...)
	{
	  char **arg = (char **) &format;
	  int c;
	  char buf[20];

	  arg++;

	  while ((c = *format++) != 0)
	    {
	      if (c != '%')
	        kputchar(c);
	      else
	        {
	          char *p;

	          c = *format++;
	          switch (c)
	            {
	            case 'd':
	            case 'u':
	            case 'x':
	              itoa (buf, c, *((int *) arg++));
	              p = buf;
	              goto string;
	              break;

	            case 's':
	              p = *arg++;
	              if (! p)
	                p = "(null)";

	            string:
	              while (*p)
	                kputchar(*p++);
	              break;

	            default:
	              kputchar(*((int *) arg++));
	              break;
	            }
	        }
	    }

}



void kputchar(char c){
	_vtflush(_vcurrentpage(), &c, 1);
}


/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access, byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}
