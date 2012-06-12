/*
 * debug.h
 *
 *  Created on: Apr 15, 2011
 */

/*
 * Archivo para realizar debbugging en el codigo y no llenar de printfs
 * Existen 4 Niveles
 * 	DEBUG_LOG
 * 	DEBUG_WARN
 *  DEBUG_ERROR
 *  DEBUG_FATAL
 *
 *  Para loggear en el codigo, simplemente incluir este archivo y escribir algo como
 *
 *  	LOG("Inicializando\n");
 *
 *  En la salida estandar se ver‡
 *
 *  	log:file:line - Inicializando
 *
 *
 *  O tambiŽn con argumentos variables
 *
 *  	WARN("Retorno: %d",ret);
 *
 *  	warn:file:line - Retorno 123
 *
 *  Para definir el nivel de debugging especificar -D como argumento.
 *
 *  Por ejemplo:
 *
 *  gcc -DDEBUG_LOG input.c -o output
 *
 *  Si no se especifica, todos los logs ser‡n eliminados
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include "klib.h"
#include "stdlib.h"

#ifdef DEBUG_LOG
	#define DEBUG_LEVEL 5
#else
	#ifdef DEBUG_WARN
		#define DEBUG_LEVEL 4
	#else
		#ifdef	DEBUG_ERROR
			#define DEBUG_LEVEL 3
		#else
			#ifdef DEBUG_FATAL
				#define DEBUG_LEVEL 2
			#else
				#define DEBUG_LEVEL 0
			#endif
		#endif
	#endif
#endif



#if (DEBUG_LEVEL > 4)
#define LOG(msg, ...)	kprintf("log:%s:%d - ", __FILE__, __LINE__); kprintf(msg,##__VA_ARGS__); kputchar('\n');
#else
#define LOG(msg, ...)
#endif

#if (DEBUG_LEVEL > 3)
#define WARN(msg, ...)	kprintf("warn:%s:%d - ", __FILE__, __LINE__); kprintf(msg,##__VA_ARGS__) kputchar('\n');
#else
#define WARN(msg, ...)
#endif

#if (DEBUG_LEVEL > 2)
#define ERROR(msg, ...)	kprintf("error:%s:%d - ", __FILE__, __LINE__); kprintf(msg,##__VA_ARGS__) kputchar('\n');
#else
#define ERROR(msg, ...)
#endif

#if (DEBUG_LEVEL > 1)
#define FATAL(msg, ...)	kprintf("fatal:%s:%d - ", __FILE__, __LINE__); kprintf(msg,##__VA_ARGS__) kputchar('\n');
#else
#define FATAL(msg, ...)
#endif



#endif /* DEBUG_H_ */
