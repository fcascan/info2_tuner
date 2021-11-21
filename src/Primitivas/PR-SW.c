/*
 * PR-SW.c
 *
 *  Created on: 14/12/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

uint8_t Teclas (void)
{
	volatile uint8_t tecla=NONE;

	if (GetPIN(SW_left, ACTIVO_BAJO)){
		tecla=LEFT;
	}
	if (GetPIN(SW_right, ACTIVO_BAJO)){
		tecla=RIGHT;
	}

	return tecla;
}
