/*
 * string.h
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#ifndef STRING_H_
#define STRING_H_

#include "types.h"

#define TO_LOWER_CASE(x) (('A'<(x) && (x) <'Z')? ((x)-'A')+'a' : (x))
#define TO_CHAR(x) ((x) + '0')


void *memcpy(void *dst, const void *src, size_t qty);
int strlen(const char *str);
void itoa (char *buf, int base, int d);
int atoi (char * s);
int strcmp(char * str1, char * str2 );
void strcpy(char *dst, char *src);
void substr(char * dst, char *src, int len, int start);
/*Saca un substring de str que este antes del separador. Si se
 * empieza por el principio, beginning debe ser distinto de 0s
 */
void token(char * dst, char * str, char sep, int beginning);
void stradd(char * dst, char * src);
void strremove(char * str, int start, int finish);

char *dataToStr(unsigned char *data, int size);


#endif /* STRING_H_ */
