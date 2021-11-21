/*
 * PR-Beep.c
 *
 *  Created on: 04/12/2014
 *      Author: Usuario
 */

#include "EA_BaseBoard.h"


void Buzz_Beep (void)
{
	volatile uint16_t i=0;
//	if (GetPIN (Buzzer, ACTIVO_BAJO)){
		SetPIN (Buzzer, ON);
		for (i=0; i<500; i++);
//	}
//	else{
		SetPIN (Buzzer, OFF);
//	}
}

