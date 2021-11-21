/*
 * Metronomo.c
 *
 *  Created on: 02/10/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

void Metronomo (void)
{
	extern uint8_t BPM[];
	extern uint8_t BPM_indice;

	static uint16_t cuenta_BMP=0;
	volatile float aux=0;

	// Aca entramos cada 5ms
	//
	// Entonces al numero 60 lo divido por el numero de BMP seleccionado actualmente,
	// de esa forma obtengo los Beeps que debo realizar por segundo (el resultado es flotante)
	// Por ejemplo: si BMP seleccionado es 184  ->  60/184 = 0,3261 segs
	// A ese resultado lo multiplico por mil y obtengo cada cuantos msegs debe sonar un Beep
	// Siguiendo el ejemplo anterior: 0,3261*1000 = 326,1 msegs
	// Ahora, a ese numero ha que dividirlo por cada cuantos msegs entro aca, o sea por 5
	// Con el ejemplo: 326,1/5 = 65,22 = 65 , o sea que cada 65 veces que entro aca hago un Beep

	cuenta_BMP++;
	aux=((float) (((float) 60/(BPM[BPM_indice]))*1000)/5);

	if (cuenta_BMP == (uint16_t) aux){
		Buzz_Beep();
		cuenta_BMP=0;
	}

	cuenta_BMP%=301;
}



