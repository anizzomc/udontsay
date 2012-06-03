/*
 * cpuid.c
 *
 *  Created on: Apr 19, 2010
 *      Author: anizzomc
 */

#include "cpuid.h"

int _cpuidLongMode();
void _cpuidString(char *array);

int cpuidLongMode(){
	return cpuidExtended() && _cpuidLongMode();
}


char *cpuidString(char *buff){

	int i;
	char chain[12];

	_cpuidString(chain);

	for(i = 0 ; i < 12 ; i++)
		buff[i] = chain[i];
	buff[12] = '\0';

	return buff;

}
