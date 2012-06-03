#include "string.h"

void *memcpy(void *dst, const void *src, size_t qty) {
		char *dstC = (char *)dst;
		char *srcC = (char *)src;

		while (qty--)
			*dstC++ = *srcC++;
		return dst;
}

int strlen(const char *str){
	int i = 0;

	while(*str){
		str++;
		i++;
	}

	return i;
}

//fuente: http://www.gnu.org/software/grub/manual/multiboot/multiboot.html
void itoa (char *buf, int base, int d)
{
   char *p = buf;
   char *p1, *p2;
   unsigned long ud = d;
   int divisor = 10;

   /* If %d is specified and D is minus, put `-' in the head. */
   if (base == 'd' && d < 0)
     {
       *p++ = '-';
       buf++;
       ud = -d;
     }
   else if (base == 'x')
     divisor = 16;

   /* Divide UD by DIVISOR until UD == 0. */
   do
     {
       int remainder = ud % divisor;

       *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
     }
   while (ud /= divisor);

   /* Terminate BUF. */
   *p = 0;

   /* Reverse BUF. */
   p1 = buf;
   p2 = p - 1;
   while (p1 < p2)
     {
       char tmp = *p1;
       *p1 = *p2;
       *p2 = tmp;
       p1++;
       p2--;
     }
 }

int
atoi(char * s)
{
	char c;
	int value=0;
	int digit;
	while ((c = *s) != 0x00 )
	{
		if ( c >= '0' && c <= '9' )
		{
			digit = (int)(c-'0');
			value = value*10+digit;
		}
		s++;
	}
	return value;
}

int
strcmp(char * str1, char * str2 )
{
	int i,j;
	i = strlen(str1);
	j = strlen(str2);

	if ( i != j)
		return 1;
	for( i = 0; i < j; i++ )
	{
		if (str1[i] != str2[i])
			return 1;
	}
	return 0;

}


void strcpy(char *dst, char *src){
	memcpy(dst, src, strlen(src)+1);
}

void substr(char * dst, char *src, int len, int start)
{
	memcpy(dst, src + start, len);
	char zero = '\0';

	memcpy(dst + len, &zero, 1);
}

void token(char * dst, char * str, char sep, int beginning)
{
	int i;
	if(beginning)
	{
		i = 0;
		while(str[i] != sep && str[i] != '\0')
			i++;
		substr(dst,str,i,0);

	}
	else
	{
		i = strlen(str);
		while(str[i] != sep && i > 0)
			i--;
		substr(dst,str,strlen(str)-i,i+1);
	}

}

void stradd(char * dst, char * src)
{

	int start = strlen(dst);

	memcpy(dst+start,src,strlen(src)+1);


}

void strremove(char * str, int start, int finish)
{
	char temp[64]={0};
	int i,j;
	j=0;
	for(i=0;i< strlen(str);i++)
	{
		if(i< start || i > finish)
			temp[j++]= str[i];
	}
	strcpy(str,temp);
}
