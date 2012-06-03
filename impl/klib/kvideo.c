/*
 * kvideo.c
 *
 *  Created on: Apr 18, 2010
 *      Author: anizzomc
 */

#include "klib.h"
#include "drivers/crtc6845.h"

//----------------------------------------------------------------------------
// Funciones de Video
//----------------------------------------------------------------------------


/**
 * Resetea la pantalla actual
 */

void kclearScreen(){
	_vresetpage(_vcurrentpage());
}

/**
 * Inicializa el video
 */
void kvinit(){
	_vinit();
	_vsetpage(0);
}
