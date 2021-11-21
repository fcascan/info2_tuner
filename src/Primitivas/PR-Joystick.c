/*
 * Joystick.c
 *
 *  Created on: 30/09/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"

	// el valor retornado por la funcion es una mascara
	// que muestra que posiciones del joystick estan
	// actualmente activas, recordar que se puede
	// activar mas de una posicion a la vez y por eso
	// es necesario implementar este tipo de estrategia

uint8_t Joystick (void)
{
	volatile uint8_t status=0;		// status=0000 0000;

	if (GetPIN(JOYSTICK_CENTER, ACTIVO_BAJO))
	{
		status |= CENTER;	// status=xxxx xxx1;
	}

	if (GetPIN(JOYSTICK_UP, ACTIVO_BAJO))
	{
		status |= UP;		// status=xxxx xx1x;
	}

	if (GetPIN(JOYSTICK_DOWN, ACTIVO_BAJO))
	{
		status |= DOWN;		// status=xxxx x1xx;
	}

	if (GetPIN(JOYSTICK_LEFT, ACTIVO_BAJO))
	{
		status |= LEFT;		// status=xxxx 1xxx;
	}

	if (GetPIN(JOYSTICK_RIGHT, ACTIVO_BAJO))
	{
		status |= RIGHT;	// status=xxx1 xxxx;
	}

	return status;			// status=000x xxxx;
}
